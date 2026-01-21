# ==============================
# LOOP – Lesen → Bewerten → Schreiben
# ==============================

from BIOS.SCHALTERKASTEN.SCHALTERKASTEN import Zustand
from BIOS.SYNAPSE.SYNAPSE import Synapse
from BIOS.EVALUATOR.EVALUATOR import Evaluator
import BIOS.SCHALTERKASTEN.SCHALTERKASTEN as config


class CognitiveLoop:
    def __init__(self):
        self.zustand = Zustand()
        self.synapse = Synapse(config.MUTATION_RATE)
        self.evaluator = Evaluator()

    def step(self):
        # Alterung
        self.zustand.alter += 1
        self.zustand.abschwaechen(config.STATE_DECAY)

        # Übergang
        self.synapse.apply(self.zustand)

        # Bewertung
        score = self.evaluator.score(self.zustand)

        return score
