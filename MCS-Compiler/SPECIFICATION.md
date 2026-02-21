# MCS Compiler Specification (Draft 0.1)

## Overview
The MCS Compiler (Maschinen-Code-Speech Compiler) translates Pylovara Logic into executable "Bausteinschaltungskreisläufe" (BSK).

## MCS Compiler Spezifikation

## Kern-Symbole & Operatoren
| Begriff | Symbol | MCS-Bedeutung (Modulator) |
| :--- | :--- | :--- |
| **Transaktionsstart** | `¢!` | `BOXH-TRANU-START` |
| **Transaktionsende** | `!¢` | `BOXAN-TRANU-ENDE` |
| **Impulsstart** | `»` | `BOXH-PULSE-START` |
| **Impulsende** | `«` | `BOXAN-PULSE-ENDE` |
| **ALU-Block** | `×` | `BOXH-ALU` |
| **Wenn (Sentiator)** | `¶` | `SENTAN-WENN-KANN` |
| **Wenn Nicht** | `¶¶` | `SENTAN-WENN-NICHT` |
| **Validieren** | `ſ` | `SENTAN-REGEL-DER-REINHEIT` |
| **Register (Langzeit)**| `Ð` | `NAVU-LANGZEITSPEICHER` |
| **Workspace (REX)** | `¬` | `REXU-SPACECREATOR` |
| **Synapse** | `Ŧ` | `Ŧ¹`, `Ŧ²`, etc. |
| **Timeout-Ende** | `«««T<NR>` | Terminierung mit T-Limit |
| **Schleifen-Ende** | `«««Ω` | Terminierung mit Endlos-Schleife |
| **Workspace-Richtung**| `¤‹`, `¤›` | Gabelung (Links/A, Rechts/B) |
| **System-Intern** | `[~...~]` | Interner System-Block |

## Fortgeschrittene Konstrukte
### Hardware & Boot
- `BOOT_SEQUENZ`: Kern-Logik für `Ŧ⁴ ¬·["BOOT-SEQUENZ"]«`.
- `FORK(RICHTUNG)`: Mapping zu `¤‹` oder `¤›`.
- `TIMEOUT(NR)`: Suffix `«««T<nr>`.
- `LOOP`: Suffix `«««Ω`.

### Biologische Analogien
- `SYNAPSE(n)`: Mapping zu `Ŧ` mit Rang `n`.
- `FEUER`: Trigger für `[× FEUER ×]`.
- `SOMA(NAME)`: Mapping zu `»["NAME"]«` mit vorangestelltem Rang.
- `DENDRIT(REIZ)`: Mapping zu `¬·»["REIZ"]«`.
- `AXON(REIZ)`: Mapping zu `¶ ¬·»["REIZ"]«`.
- `EMOTION_LOOKUP(KEY)`: Mapping zu `»[~EMOTION-LOOKUP KEY="KEY"~]«`.
- `APPLY_BIO(EFFEKT)`: Mapping zu `»[× APPLY-BIOCHEM EFFEKT ×]«`.

### Synchronisation & Taktung
- `SYNC_8TAKT`: 8-Takt-Kernel Aufruf und Matrix-Sync.
- `HEARTBEAT(LABEL)`: Synchronisations-Startpunkt am Aktionsdraht.
- `WAIT(TAKTE)`: Mapping zu `»[× TIMEOUT TAKTE ×]«`.

### Feed-Logistik & Proteine
- `FEED_ASSIGN(NR, WERT)`: Mapping zu `¬·¤= »["(NR)±WERT±"]«`.
- `FEED_READ(NR)`: Mapping zu `±WERT±(NR)`.
- `TRANSFER(ZIEL, DATEN)`: Mapping zu `»[~TRANSFER ZIEL~|"DATEN"]«`.
- `EXTRACT(LABEL, QUELLE)`: Mapping zu `»[~EXTRACT LABEL~|"QUELLE"]«`.
- `PROTEIN(INHALT)`: Datencontainer `»[~PROTEIN INHALT~]«`.

### MCS-CMD Prozess- & Dateibefehle (Note 016)
- `PROZESS_START(PROZ)`: `START-<PROZESS>`
- `PROZESS_STOP(PROZ)`: `STOP-<PROZESS>`
- `PROZESS_RESTART(PROZ)`: `NEUSTART-<PROZESS>`
- `PROZESS_STATUS(PROZ)`: `STATUS-<PROZESS>`
- `AKTIVIEREN(PROG)`: `AKTIVIEREN-<PROGRAMM>`
- `DEAKTIVIEREN(PROG)`: `DEAKTIVIEREN-<PROGRAMM>`
- `ERZEUGE_CORE`: `ERZEUGE-CORE`
- `ERZEUGE_NEEDLE`: `ERZEUGE-NEEDLE`
- `PROGRAMMIERUNG`: `MCCH-PROGRAMMIERUNG`

## Zielformat: .MCS / .BSK
Die Ausgabe ist ein Symbol-Strang gemäß den `ABSOLULATOR` Modulationssequenzen.

Example Sequence (ALU Operation):
`¢! » [ × ALU-OP × ] « !¢`
