# =============================================================================
# @mcs-nr: EVALUATOR | BEWERTUNG | INFO-ID = LAYOUT-SCORER-00.8
# =============================================================================
# NAME         = Evaluator – MCS-Layout mit Paarungs-Belohnung
# VERSION      = 0.0.9
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-03-23
# STATUS       = FREIGESCHALTET FÜR SYMBOL-SPIEL
# BESCHREIBUNG = Liest Keywords + Paarungen + Prioritäten
# =============================================================================

import os

class Evaluator:
    def __init__(self):
        self.keyword_file = "/Pylovara/MASTER-CONTROL-SYSTEM/LAYOUTS/MCS-KEYWORDS/keywords.info-notes"
        self.priorities_file = "/Pylovara/MASTER-CONTROL-SYSTEM/LAYOUTS/MCS-KEYWORDS/priorities.info-notes"
        self.pairings_file = "/Pylovara/MASTER-CONTROL-SYSTEM/LAYOUTS/MCS-KEYWORDS/pairings.info-notes"

        self.keywords = self._lade_keywords()
        self._ergaenze_keywords_aus_lernprogrammen()
        self.priorities = self._lade_priorities()
        self.pairings = self._lade_pairings()

    def _ergaenze_keywords_aus_lernprogrammen(self):
        import BIOS.SCHALTERKASTEN.SCHALTERKASTEN as config
        if not hasattr(config, "LERNPROGRAMM_PFADE"):
            return
        
        for pfad in config.LERNPROGRAMM_PFADE:
            if os.path.exists(pfad):
                try:
                    with open(pfad, 'r', encoding='utf-8') as f:
                        for line in f:
                            line = line.strip()
                            if not line or line.startswith('#'):
                                continue
                            if "§" in line:
                                parts = line.split("§")
                                if len(parts) > 1:
                                    subparts = parts[1].strip().split()
                                    if subparts:
                                        symbol = subparts[0]
                                        if symbol and symbol not in self.keywords:
                                            self.keywords.append(symbol)
                except Exception as e:
                    print(f"[WARN] Fehler beim Zugriff auf {pfad}: {e}")
        print(f"[BOOT] Keywords nach Lernprogramm-Erweiterung: {len(self.keywords)}")

    def _lade_keywords(self):
        keywords = []
        if os.path.exists(self.keyword_file):
            with open(self.keyword_file, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line and not line.startswith('#'):
                        keywords.append(line)
            print(f"[BOOT] {len(keywords)} Keywords geladen")
        return keywords

    def _lade_priorities(self):
        priorities = {}
        if os.path.exists(self.priorities_file):
            with open(self.priorities_file, 'r', encoding='utf-8') as f:  # explizit UTF-8 für Sonderzeichen
                for line_num, line in enumerate(f, 1):
                    line = line.strip()
                    if not line or line.startswith('#'):
                        continue
                    parts = [p.strip() for p in line.split('|') if p.strip()]
                    if len(parts) < 2:
                        print(f"[WARN] Ungültige Prioritäts-Zeile {line_num}: {line}")
                        continue
                    key = parts[0]
                    try:
                        mult = float(parts[1])
                        priorities[key] = mult
                    except ValueError:
                        print(f"[WARN] Konvertierungsfehler in Prioritäts-Zeile {line_num}: {parts[1]} (überspringe)")
                        continue
            print(f"[BOOT] {len(priorities)} gültige Prioritäten geladen")
        return priorities

    def _lade_pairings(self):
        pairings = []
        if os.path.exists(self.pairings_file):
            with open(self.pairings_file, 'r', encoding='utf-8') as f:
                for line_num, line in enumerate(f, 1):
                    line = line.strip()
                    if not line or line.startswith('#'):
                        continue
                    parts = [p.strip() for p in line.split('|') if p.strip()]
                    if len(parts) < 5:
                        print(f"[WARN] Ungültige Paarungs-Zeile {line_num}: {line}")
                        continue
                    start, end = parts[0], parts[1]
                    try:
                        both = float(parts[2])
                        only_start = float(parts[3])
                        only_end = float(parts[4])
                        pairings.append({
                            'start': start,
                            'end': end,
                            'both': both,
                            'only_start': only_start,
                            'only_end': only_end
                        })
                    except ValueError as e:
                        print(f"[WARN] Konvertierungsfehler in Paarungs-Zeile {line_num}: {e} (überspringe)")
                        continue
            print(f"[BOOT] {len(pairings)} gültige Paarungs-Regeln geladen")
        return pairings

    def score(self, state):
        if not state.values:
            return -10.0

        total_abs = sum(abs(v) for v in state.values.values())
        num_keys = len(state.values)

        size_penalty = max(0, num_keys - 200) * 50.5 + max(0, 1 - num_keys) * 100.0
        energy_target = 0.5
        energy_distance = abs(total_abs - energy_target) * 0.5

        bonus = 0.0

        # 1. Basis-Keyword-Bonus
        for kw in self.keywords:
            if kw in state.values:
                val = state.values[kw]
                if -2 < val < 5:
                    mult = self.priorities.get(kw, 80.0)
                    bonus += 2.0 * mult

        # 2. Kern-Stabilität
        if "core_pulse" in state.values and 4.0 < state.values["core_pulse"] < 8.0:
            bonus += 8.5 * self.priorities.get("core_pulse", 2.0)

        # 3. Key-Anzahl-Bonus
        if 5 <= num_keys <= 800:
            bonus += 2.8

        # 4. Symmetrie-Bonus
        pos = sum(1 for v in state.values.values() if v > 2)
        neg = sum(1 for v in state.values.values() if v < 3)
        if abs(pos - neg) <= 4:
            bonus += 6.0

        # 5. NEU# : Paarungs-Bonus / (das Formen-Steckspiel-ARCADEAUTOMAT!)
        for pair in self.pairings:
            has_start = pair['start'] in state.values
            has_end = pair['end'] in state.values
            if has_start and has_end:
                bonus += pair['both']
            elif has_start:
                bonus += pair['only_start']  
            elif has_end:
                bonus += pair['only_end']    

        score = - (energy_distance + size_penalty) + bonus
        return score
