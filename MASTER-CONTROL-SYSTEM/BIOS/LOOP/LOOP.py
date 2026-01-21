# ==============================
# LOOP – Lesen → Bewerten → Schreiben
# ==============================

from BIOS.SCHALTERKASTEN.SCHALTERKASTEN import Zustand
from BIOS.SYNAPSE.SYNAPSE import Synapse
from BIOS.EVALUATOR.EVALUATOR import Evaluator
import BIOS.SCHALTERKASTEN.SCHALTERKASTEN as config

class Zustand:
    def __init__(self):
        self.werte = {}
        self.alter = 0

    def aktualisieren(self, schluessel, delta):
        self.werte[schluessel] = self.werte.get(schluessel, 0.0) + delta

    def abschwaechen(self, rate):
        for k in self.werte:
            self.werte[k] *= (1.0 - rate)

    def abbild(self):
        return dict(self.werte)
