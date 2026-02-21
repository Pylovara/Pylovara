import time
import sys
import random
import os

# ANSI Farben für das Terminal
GRUEN = "\033[32m"
BLAU = "\033[34m"
ROT = "\033[31m"
CYAN = "\033[36m"
GELB = "\033[33m"
RESET = "\033[0m"
FETT = "\033[1m"

class MCSVisualisierer:
    def __init__(self, mcs_code):
        self.code = mcs_code
        self.matrix_breite = 40
        self.matrix_hoehe = 15
        self.matrix = [[" " for _ in range(self.matrix_breite)] for _ in range(self.matrix_hoehe)]

    def loesche_terminal(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def zeichne_matrix(self, status_text="Bereit..."):
        self.loesche_terminal()
        print(f"{FETT}{GELB}=== PYLOVARA MCS GATTER-SHOW (Nanosekunden-Kaskade) ==={RESET}")
        print(f"{CYAN}Status: {status_text}{RESET}\n")
        
        # Obere Begrenzung
        print("+" + "-" * (self.matrix_breite) + "+")
        for zeile in self.matrix:
            print("|" + "".join(zeile) + "|")
        print("+" + "-" * (self.matrix_breite) + "+")
        
        print(f"\n{GRUEN}Fliedende Symbole: {self.code[:70]}{'...' if len(self.code) > 70 else ''}{RESET}")

    def animiere_impuls(self, symbol, farbe=GRUEN):
        # Simuliert einen Impuls, der durch die Matrix wandert
        zeile = random.randint(0, self.matrix_hoehe - 1)
        for spalte in range(self.matrix_breite):
            # Vorheriges Zeichen löschen/ändern
            if spalte > 0:
                self.matrix[zeile][spalte-1] = "·"
            
            self.matrix[zeile][spalte] = f"{farbe}{symbol}{RESET}"
            self.zeichne_matrix(f"Impuls verarbeitet: {symbol}")
            time.sleep(0.02)
        
        # Spur hinterlassen
        self.matrix[zeile][self.matrix_breite-1] = "·"

    def zeige_kaskade(self, block_id):
        # Zeigt einen statischen Kaskadenblock (20x20) wie in Note 015
        self.loesche_terminal()
        print(f"{FETT}{ROT}[CASCADE-{block_id}]{RESET}")
        for _ in range(10):
            reihe = "".join([random.choice(["#", ".", " ", "þ", "×"]) for _ in range(40)])
            print(f"{GRUEN}{reihe}{RESET}")
            time.sleep(0.1)
        time.sleep(0.5)

    def starte_show(self):
        # Zerlege MCS Code grob in "Events"
        # Dies ist eine vereinfachte Darstellung für die Show
        symbole = self.code.split()
        
        for sym in symbole:
            if sym == "¢!":
                self.animiere_impuls("¢", BLAU)
            elif sym == "!¢":
                self.animiere_impuls("!", BLAU)
            elif sym == "»":
                self.animiere_impuls(">", GRUEN)
            elif sym == "«":
                self.animiere_impuls("<", GRUEN)
            elif sym.startswith("þ"):
                # Identitäts-Stempel
                for _ in range(len(sym)):
                    self.animiere_impuls("þ", GELB)
            elif "×" in sym:
                # ALU Operation
                self.animiere_impuls("×", ROT)
            elif "[" in sym or "]" in sym:
                self.animiere_impuls(sym, CYAN)
            elif "Ŧ" in sym:
                self.animiere_impuls("Ŧ", CYAN)
            else:
                # Text oder unbekannte Symbole
                if len(sym) > 1:
                    self.animiere_impuls("?", BLAU)
                else:
                    self.animiere_impuls(sym, GRUEN)
            
            time.sleep(0.1)

        self.zeichne_matrix("Kaskade abgeschlossen.")
        print(f"\n{FETT}{GELB}Transfer beendet.{RESET}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        beispiel_mcs = "¢! þþ » [ × ADD 10 20 × ] « ſ [~OK~] !¢"
    else:
        beispiel_mcs = sys.argv[1]
        
    show = MCSVisualisierer(beispiel_mcs)
    show.starte_show()
