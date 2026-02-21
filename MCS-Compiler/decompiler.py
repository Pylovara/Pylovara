import re
import sys

# Rückwärts-Zuordnung basierend auf SPECIFICATION.md und compiler.py
REVERSE_MAP = {
    "¢!": "TRANSACTION_START",
    "!¢": "TRANSACTION_END",
    "»": "PULSE_START",
    "«": "PULSE_END",
    "þ": "þ", # Wird dynamisch für Ebenen behandelt
    "ſ": "VALIDATE",
    "Ŧ": "SYNAPSE", # Wird dynamisch für Ränge behandelt
    "×": "×", # Wird im Block-Kontext behandelt
}

class MCSDecompiler:
    def __init__(self, mcs_code):
        self.code = mcs_code
        self.tokens = []

    def tokenize(self):
        # Tokenisierung nach Symbolen, Klammern und Strings (Spezifische Muster zuerst!)
        self.tokens = re.findall(r'START-<[^>]*>|STOP-<[^>]*>|ERZEUGE-[A-Z]+|MCCH-[A-Z]+|±WERT±\(\d+\)|¬·¤=|þ+|Ŧ[⁰¹²³⁴⁵⁶⁷⁸⁹]*|[~[^~]*~]|\"[^\"]*\"|\[|\]|»|«|¢!|!¢|ſ|×|\w+|[><=!/]+', self.code)
        return self.tokens

    def decompile(self):
        self.tokenize()
        ausgabe = []
        stack = []
        
        i = 0
        while i < len(self.tokens):
            token = self.tokens[i]
            
            # Einfache Schlüsselwörter
            if token == "¢!":
                ausgabe.append("TRANSACTION_START")
            elif token == "!¢":
                ausgabe.append("TRANSACTION_END")
            elif token == "»":
                # Impuls oder Boxis? Blick nach vorn!
                if i + 2 < len(self.tokens) and self.tokens[i+1] == "[" and self.tokens[i+2] != "×":
                    ausgabe.append("BOXIS_CALL [")
                    stack.append("BOXIS")
                    i += 1
                else:
                    ausgabe.append("PULSE_START")
            elif token == "«":
                ausgabe.append("PULSE_END")
            elif token == "¶":
                if i + 1 < len(self.tokens) and self.tokens[i+1] == "[":
                    ausgabe.append("IF [")
                    stack.append("IF")
                    i += 1
                else:
                    ausgabe.append("IF")
            elif token == "¶¶":
                ausgabe.append("IF_NOT")
                
            # Identitäts-Logik
            elif token.startswith("þ"):
                ebene = len(token)
                ausgabe.append(f"IDENTIFY {ebene}")
                
            # Biologisch / Synaptisch
            elif token.startswith("Ŧ"):
                rang = self.von_hochgestellt(token[1:])
                # Prüfung auf BOOT_SEQUENZ: Ŧ⁴ ¬·["BOOT-SEQUENZ"]«
                if rang == "4" and i + 1 < len(self.tokens) and "BOOT-SEQUENZ" in self.tokens[i+1]:
                    ausgabe.append("BOOT_SEQUENZ")
                    i += 1
                    if i + 1 < len(self.tokens) and self.tokens[i+1] == "«": i += 1
                else:
                    ausgabe.append(f"SYNAPSE {rang}")
                    
            elif token == "ſ":
                if i + 1 < len(self.tokens):
                    aktion = self.tokens[i+1].strip("[~]~")
                    ausgabe.append(f"VALIDATE \"{aktion}\"")
                    i += 1
                    
            # Feeds & Prozesse (Note 016)
            elif token == "¬·¤=":
                if i + 1 < len(self.tokens):
                    val_match = re.search(r'\((\d+)\)±(.*)±', self.tokens[i+1])
                    if val_match:
                        nr, val = val_match.groups()
                        ausgabe.append(f"FEED_ASSIGN {nr} \"{val}\"")
                        i += 1
            elif token.startswith("±WERT±"):
                nr_match = re.search(r'\((\d+)\)', token)
                if nr_match:
                    ausgabe.append(f"FEED_READ {nr_match.group(1)}")
            elif token.startswith("START-<"):
                proz = token[7:-1]
                ausgabe.append(f"PROZESS_START \"{proz}\"")
            elif token.startswith("STOP-<"):
                proz = token[6:-1]
                ausgabe.append(f"PROZESS_STOP \"{proz}\"")
            elif token == "ERZEUGE-CORE":
                ausgabe.append("ERZEUGE_CORE")
            elif token == "ERZEUGE-NEEDLE":
                ausgabe.append("ERZEUGE_NEEDLE")
            elif token == "MCCH-PROGRAMMIERUNG":
                ausgabe.append("PROGRAMMIERUNG")
            
            # Interna / Klammern
            elif token == "[":
                if i + 1 < len(self.tokens) and self.tokens[i+1] == "×":
                    ausgabe.append("ALU [")
                    stack.append("ALU")
                    i += 1
                else:
                    ausgabe.append("[")
            elif token == "×":
                if i + 1 < len(self.tokens) and self.tokens[i+1] == "]":
                    i += 1
                    if stack and stack[-1] == "ALU":
                        ausgabe.append("]")
                        stack.pop()
                    else:
                        ausgabe.append("× ]")
            elif token == "]":
                if stack:
                    ctx = stack.pop()
                    if ctx == "IF": ausgabe.append("] END_IF")
                    elif ctx == "BOXIS": ausgabe.append("]")
                    else: ausgabe.append("]")
                else:
                    ausgabe.append("]")
            
            # Strings / Boxis-Inhalt
            elif token.startswith("\"") and token.endswith("\""):
                ausgabe.append(token)
            elif token.startswith("[~") and token.endswith("~]"):
                inhalt = token[2:-2]
                if "EMOTION-LOOKUP" in inhalt:
                    key_match = re.search(r'KEY="([^"]*)"', inhalt)
                    key = key_match.group(1) if key_match else "None"
                    ausgabe.append(f"EMOTION_LOOKUP \"{key}\"")
                else:
                    # Wenn es ein einfacher String im internen Block ist, als VALIDATE oder INTERNAL behandeln
                    ausgabe.append(f"\"{inhalt}\"")
            
            else:
                # Literale oder sonstige Fragmente
                if token not in ["~]", "[~"]: # Sicherungskorrektur für gesplitte interne Blöcke
                    ausgabe.append(token)
            i += 1
            
        return " ".join(ausgabe)

    def von_hochgestellt(self, s):
        hochgestellt = "⁰¹²³⁴⁵⁶⁷⁸⁹"
        ziffern = "0123456789"
        trans = str.maketrans(hochgestellt, ziffern)
        return s.translate(trans) if s else "1"

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Verwendung: python3 decompiler.py \"<mcs_code>\"")
        sys.exit(1)
        
    code = sys.argv[1]
    decompiler = MCSDecompiler(code)
    ergebnis = decompiler.decompile()
    print("Dekompilierter Pylovara-Code:")
    print(ergebnis)
