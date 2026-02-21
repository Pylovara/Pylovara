import re
import sys

# MCS Symbol-Zuordnung (basierend auf SCHABLONATOR 31 und Note 016)
MCS_SYMBOLE = {
    "TRANSACTION_START": "¢!",
    "TRANSACTION_END": "!¢",
    "PULSE_START": "»",
    "PULSE_END": "«",
    "ALU_START": "×",
    "ALU_END": "×",
    "POIU_START": "[",
    "POIAN_ENDE": "]",
    "IF_START": "¶",
    "IF_NOT": "¶¶",
    "REPORT_START": "\"",
    "REPORT_END": "\"",
}

class MCSCompiler:
    def __init__(self, quellcode):
        self.quellcode = quellcode
        self.tokens = []

    def tokenize(self):
        # Kommentare entfernen
        code_ohne_kommentare = re.sub(r'#.*', '', self.quellcode)
        # Verbesserter Tokenizer für Klammern und Strings (jetzt auch mit Umlauten etc.)
        self.tokens = re.findall(r'\"[^\"]*\"|\[|\]|\w+|[><=!]+', code_ohne_kommentare)
        return self.tokens

    def compile(self):
        self.tokenize()
        ausgabe = []
        stack = []
        
        i = 0
        while i < len(self.tokens):
            token = self.tokens[i]
            
            # Kern-Konstrukte
            if token == "TRANSACTION_START":
                ausgabe.append("¢!")
            elif token == "TRANSACTION_END":
                ausgabe.append("!¢")
            elif token == "PULSE_START":
                ausgabe.append("»")
            elif token == "PULSE_END":
                ausgabe.append("«")
            elif token == "ALU":
                ausgabe.append("[ ×")
                stack.append("ALU")
                if i + 1 < len(self.tokens) and self.tokens[i+1] == "[": i += 1
            elif token == "IF":
                ausgabe.append("¶ [")
                stack.append("IF")
                if i + 1 < len(self.tokens) and self.tokens[i+1] == "[": i += 1
            elif token == "BOXIS_CALL":
                ausgabe.append("» [")
                stack.append("BOXIS")
                if i + 1 < len(self.tokens) and self.tokens[i+1] == "[": i += 1
            
            # Identitäts-Logik
            elif token == "IDENTIFY":
                ebene = 1
                if i + 1 < len(self.tokens) and self.tokens[i+1].isdigit():
                    ebene = int(self.tokens[i+1])
                    i += 1
                ausgabe.append("þ" * ebene)
            elif token == "VALIDATE":
                if i + 1 < len(self.tokens):
                    aktion = self.tokens[i+1].strip('"')
                    ausgabe.append(f"ſ [~{aktion}~]")
                    i += 1
            
            # Ausgabe & Kommunikation
            elif token == "SAY":
                if i + 1 < len(self.tokens):
                    text = self.tokens[i+1].strip('"')
                    ausgabe.append(f"»[\"{text}\"]«")
                    i += 1
            elif token == "RUN_SHELL":
                if i + 1 < len(self.tokens):
                    befehl = self.tokens[i+1].strip('"')
                    ausgabe.append(f"»['{befehl}']«")
                    i += 1
            elif token == "OS_CALL":
                if i + 1 < len(self.tokens):
                    name = self.tokens[i+1].strip('"')
                    ausgabe.append(f"»[,{name},]«")
                    i += 1
            
            # Hardware & Biologie
            elif token == "CASCADE":
                block_id = self.tokens[i+1] if i + 1 < len(self.tokens) else "X"
                ausgabe.append(f"\n[CASCADE-{block_id}]\n" + ("#" * 20 + "\n") * 5 + "[/CASCADE]\n")
                if i + 1 < len(self.tokens): i += 1
            elif token == "BOOT_SEQUENZ":
                ausgabe.append("Ŧ⁴ ¬·[\"BOOT-SEQUENZ\"]«")
            elif token == "SYNAPSE":
                rang = ""
                if i + 1 < len(self.tokens) and self.tokens[i+1].isdigit():
                    rang = self.zu_hochgestellt(int(self.tokens[i+1]))
                    i += 1
                ausgabe.append(f"Ŧ{rang}")
            elif token == "FORK":
                richtung = "¤:"
                if i + 1 < len(self.tokens):
                    if self.tokens[i+1] == "LEFT": richtung = "¤‹"; i += 1
                    elif self.tokens[i+1] == "RIGHT": richtung = "¤›"; i += 1
                ausgabe.append(richtung)
            elif token == "SOMA":
                name = self.tokens[i+1].strip('"') if i + 1 < len(self.tokens) else "Soma"
                ausgabe.append(f"»[\"{name}\"]«")
                if i + 1 < len(self.tokens): i += 1
            elif token == "DENDRITE":
                reiz = self.tokens[i+1].strip('"') if i + 1 < len(self.tokens) else "Dendrit"
                ausgabe.append(f"¬·»[\"{reiz}\"]«")
                if i + 1 < len(self.tokens): i += 1
            elif token == "AXON":
                reiz = self.tokens[i+1].strip('"') if i + 1 < len(self.tokens) else "Axon"
                ausgabe.append(f"¶ ¬·»[\"{reiz}\"]«")
                if i + 1 < len(self.tokens): i += 1
            elif token == "FEUER":
                ausgabe.append("¶ [× FEUER ×]«")
            
            # Synchronisation
            elif token == "SYNC_8TAKT":
                ausgabe.append("»['exec /Pylovara/System/Module/8taktryhtmus.system-kernel']« ¶ ¬· »[~SYNC MATRIX~]«")
            elif token == "HEARTBEAT":
                label = self.tokens[i+1].strip('"') if i + 1 < len(self.tokens) else "SYNC"
                ausgabe.append(f"# ↓HERZSCHLAG-{label}-aktionsdraht-startpunkt")
                if i + 1 < len(self.tokens): i += 1
            elif token == "WAIT":
                takte = self.tokens[i+1] if i + 1 < len(self.tokens) else "0"
                ausgabe.append(f"»[× TIMEOUT {takte} TAKTE ×]«")
                if i + 1 < len(self.tokens): i += 1

            # Feed-Logistik
            elif token == "FEED_ASSIGN":
                nr = self.tokens[i+1] if i + 1 < len(self.tokens) else "0"
                wert = self.tokens[i+2].strip('"') if i + 2 < len(self.tokens) else ""
                ausgabe.append(f"¬·¤= »[\"({nr})±{wert}±\"]«")
                if i + 2 < len(self.tokens): i += 2
            elif token == "FEED_READ":
                nr = self.tokens[i+1] if i + 1 < len(self.tokens) else "0"
                ausgabe.append(f"±WERT±({nr})")
                if i + 1 < len(self.tokens): i += 1
            
            # MCS-CMD Erweiterungen (Note 016)
            elif token == "PROZESS_START":
                proz = self.tokens[i+1].strip('"') if i+1 < len(self.tokens) else "ELEMENT"
                ausgabe.append(f"START-<{proz}>")
                if i+1 < len(self.tokens): i += 1
            elif token == "PROZESS_STOP":
                proz = self.tokens[i+1].strip('"') if i+1 < len(self.tokens) else "ELEMENT"
                ausgabe.append(f"STOP-<{proz}>")
                if i+1 < len(self.tokens): i += 1
            elif token == "ERZEUGE_CORE":
                ausgabe.append("ERZEUGE-CORE")
            elif token == "ERZEUGE_NEEDLE":
                ausgabe.append("ERZEUGE-NEEDLE")
            elif token == "PROGRAMMIERUNG":
                ausgabe.append("MCCH-PROGRAMMIERUNG")

            # Hilfs-Logik
            elif token == "INTERNAL":
                if i + 1 < len(self.tokens):
                    cmd = self.tokens[i+1].strip('"')
                    ausgabe.append(f"[~{cmd}~]")
                    i += 1
            elif token == "]":
                if stack:
                    ctx = stack.pop()
                    if ctx == "ALU": ausgabe.append("× ]")
                    elif ctx == "IF": ausgabe.append("]")
                    elif ctx == "BOXIS": ausgabe.append("] «")
                else:
                    ausgabe.append("]")
            elif token == "END_IF":
                pass
            else:
                ausgabe.append(token)
            i += 1
        
        return " ".join(ausgabe)

    def zu_hochgestellt(self, n):
        # Hilfsfunktion für Synapsen-Ränge
        hochgestellt = str.maketrans("0123456789", "⁰¹²³⁴⁵⁶⁷⁸⁹")
        return str(n).translate(hochgestellt)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Verwendung: python3 compiler.py <quelldatei>")
        sys.exit(1)
        
    with open(sys.argv[1], 'r') as f:
        code = f.read()
        
    compiler = MCSCompiler(code)
    ergebnis = compiler.compile()
    print("Kompilierter MCS-Code:")
    print(ergebnis)
