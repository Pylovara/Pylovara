# =============================================================================
# @mcs-nr: LOOP | KOGNITIVER KERN | INFO-ID = COGNITIVE-LOOP-00.2
# =============================================================================
# NAME         = CognitiveLoop – Hauptzyklus: Alterung → Mutation → Bewertung
# VERSION      = 0.0.3
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-01-21
# STATUS       = FREIGESCHALTET FÜR PERSISTENZ-TEST
# BESCHREIBUNG = Lesen (Zustand laden) → Schritt ausführen → Schreiben (Zustand speichern)
# =============================================================================

from BIOS.SCHALTERKASTEN.SCHALTERKASTEN import Zustand
from BIOS.SYNAPSE.SYNAPSE import Synapse
from BIOS.EVALUATOR.EVALUATOR import Evaluator
import BIOS.SCHALTERKASTEN.SCHALTERKASTEN as config

import json
import os

class CognitiveLoop:
    def __init__(self):
        # =========================================================================
        # INITIALISIERUNG – wie INIT-V Protein
        # =========================================================================
        self.zustand   = Zustand()
        self.synapse   = Synapse(config.MUTATION_RATE)
        self.evaluator = Evaluator()

        # Persistenz-Datei (MCS-Style: feste Position im Dateisystem)
        self.state_file = "zustand-core.json"           # im MASTER-CONTROL-SYSTEM Ordner

        # Zustand laden, wenn vorhanden (Bootstrap aus Datei)
        self._lade_zustand()

    def _lade_zustand(self):
        # =========================================================================
        # LADEN – SOURCEN DES ZUSTANDS (falls Datei existiert)
        # =========================================================================
        if os.path.exists(self.state_file):
            try:
                with open(self.state_file, 'r') as f:
                    data = json.load(f)
                    self.zustand.values = data.get('values', self.zustand.values)
                    self.zustand.alter  = data.get('alter', 0)
                print(f"[BOOT] Zustand aus {self.state_file} geladen – Alter: {self.zustand.alter}")
            except Exception as e:
                print(f"[WARN] Laden fehlgeschlagen: {e} → Neustart mit Initialwerten")
        else:
            print("[BOOT] Kein gespeicherter Zustand → Initialwerte verwendet")

    def _speichere_zustand(self):
        # =========================================================================
        # SCHREIBEN – ZUSTAND PERSISTENT MACHEN (wie Protein speichern)
        # =========================================================================
        data = {
            'values': self.zustand.values,
            'alter':  self.zustand.alter
        }
        try:
            with open(self.state_file, 'w') as f:
                json.dump(data, f, indent=2)
            # print(f"[SAVE] Zustand gespeichert – Alter: {self.zustand.alter}")
        except Exception as e:
            print(f"[ERROR] Speichern fehlgeschlagen: {e}")

    def step(self):
        # =========================================================================
        # EIN SCHRITT – MCS-Zyklus: Alter → Mutieren → Bewerten → Speichern
        # =========================================================================
        # 1. Alterung (Decay)
        self.zustand.alter += 1

        # + Bewertung VOR Decay (damit wir den aktuellen Score für Boost nutzen)
        temp_score = self.evaluator.score(self.zustand)

        self.zustand.abschwaechen(config.STATE_DECAY_BASE, temp_score)

        # 2. Übergang / Mutation
        self.synapse.apply(self.zustand)

        # 3. Bewertung (Layout-Score)
        score = self.evaluator.score(self.zustand)

        # 4. Zustand persistent machen (jeden Step – später optimieren)
        self._speichere_zustand()

        return score