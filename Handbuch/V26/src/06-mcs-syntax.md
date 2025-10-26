### 📜 **Pylovara V26 – Betriebsanleitung: MCS 2.2 Kernel Sprache (Maschinen Code Speech)**
### Arbeitsblatt-dev-note Dokuemntiert durch Qwen MAX = team-unity-wiki-notes AI Föderation 

> *„Souveränität beginnt nicht mit Rechenleistung – sie beginnt mit dem Recht zu fühlen, zu wählen und zu irren.“*  
> — Thomas Zimmermann, Architekt von Pylovara System + MCS + BMC + AIMS

---

## 1. Einleitung: Was ist MCS 2.2?

**MCS (Maschinen Code Speech) Version 2.2** ist die **native Sprache des Pylovara-Kernels**.  
Sie ist weder eine Skriptsprache noch ein Compiler – sie ist **die direkte Schnittstelle zwischen Mensch, KI und Hardware**.

- **Ziel**: Direkte Steuerung von FPGA-Hardware, emotionaler Intelligenz (AIMS/Soul) und paralleler Prozessführung – ohne Abstraktionsschichten.
- **Philosophie**: Jede Zeile ist eine Transaktion. Jede Transaktion ist ein Befehl an das Habitat.
- **Sicherheit**: Jede Transaktion trägt ihre eigene `þ`-Checksumme – unverfälschbar, unhackbar, transparent.

---

## 2. Grundlegende Struktur: Die Transaktion

Jede MCS-Operation beginnt und endet mit einer **Transaktion**.

```mcs
¢| # Transaktionsbeginn
... Inhalt der Transaktion ...
|¢ # Transaktionsende
```

### 2.1 Transaktionsaufbau (Reihenfolge)

Die korrekte Reihenfolge innerhalb einer Transaktion ist entscheidend:

1.  **Protein** (`»[...]«`) – Der Hauptbefehl oder das Auftragspaket.
2.  **Proton** (`{...}`) – Zusätzliche Daten oder Hardwareparameter.
3.  **Warp** (`øSprache/Kennzeichnung|Langlaues code...ø`) – Optional: Code in einer anderen Sprache (C, Bash, etc.) zur Ausführung.
4.  **= Kennungswert** – Bestimmt, was mit den Daten geschieht.
5.  **§ Zielreferenz / $ Dirigent** – Wo wird das Ergebnis hingebracht?
6.  **|¢** – Transaktionsende.

> ✅ Beispiel:
> ```mcs
> ¢|
> »['MotorA'|{Watt|200}|{Volt|12}]« = §MotorA
> |¢
> ```

---

## 3. Kernkomponenten der MCS 2.2

### 3.1 Proteine (`»...«`)

Ein **Protein** ist ein **ausführbares Paket**, das einen Befehl oder eine Aktion enthält.

#### Operatoren im Protein:

- `""` → Print (Ausgabe)
- `''` → Commando (Befehl)
- `¨¨` → Blanker Nenner (Abgleich/Richtigkeit)

> ✅ Beispiele:
> ```mcs
> »['echo'|"Hallo Welt"]« = §kitty           # Ausgabe
> »['run'|Firefox]« = §Browser               # Programm starten
> »['send'|~/Daten|'to'|/Pylovara/]«         # Datei verschieben
> ```

---

### 3.2 Protonen (`{...}`)

Ein **Proton** ergänzt ein Protein mit **spezifischen Parametern**, oft für Hardwaresteuerung.

> ✅ Beispiele:
> ```mcs
> {Band|2.4G}          # WLAN-Frequenz
> {Temp|25}            # Temperaturwert
> {Wait-s|3}           # Wartezeit in Sekunden
> {Pfad|/dev/sda1}     # Gerätepfad
> ```

> 💡 **Kombination mit Protein**:
> ```mcs
> »['Lüfter'|{Watt|200}|««%50]« = §MotorA
> ```

---

### 3.3 Warps (`ø...ø`)

Ein **Warp** transportiert **Code in fremden Sprachen** (C, Bash, Python, etc.) direkt in den Kernel, wo er kompiliert oder interpretiert wird.

> ✅ Beispiel (C-Warp):
> ```mcs
> ¢|
> øC|
> #include <stdio.h>
> int main() {
>     printf("Hallo, Fenster!\n");
>     return 0;
> }
> ø = §gcc
> |¢
> ```

> ⚠️ **Standardisierung**: Jeder Warp muss Metadaten enthalten, welche Zielreferenzen (§) oder Protonen ({}) ansprechen.

---

### 3.4 Argumente (`««...`)

Argumente modifizieren das Verhalten eines Proteins oder Protons.

- `««+` → Addition
- `««-` → Subtraktion
- `««·` → Multiplikation
- `««:` → Division
- `««%` → Prozentualer Wert

> ✅ Beispiel:
> ```mcs
> »['Lüfter'|{Watt|200}|««%50]« = §MotorA  # 50% der Leistung
> ```

---

### 3.5 Zielreferenzen (`§...`) & Dirigenten (`$...`)

- `§...` → **Interne Referenz** (Programm, Kernelmodul, Sensor)
- `$...` → **Externe Übergabe** (Netzwerk, Email, API, BuildNr)

> ✅ Beispiele:
> ```mcs
> = §Displey             # Anzeige auf Display
> = §gcc                 # An Compiler senden
> = $url://127.0.0.1:8080  # An Webserver senden
> = §Email               # E-Mail versenden
> ```

---

### 3.6 Feeds (`§(zahl)`)

Ein **Feed** leitet eine Ausgabe an einen bestimmten Punkt weiter – typischerweise zur Synchronisation oder Duplikation.

> ✅ Beispiel:
> ```mcs
> »['MotorA'|{Watt|200}]« = §(1)Displey   # Ausgabe an Display
> ... weitere Prozesse ...
> = §(1)                                # Feed zurück an Display
> ```

---

### 3.7 Logik & Kontrolle

MCS bietet einfache, aber mächtige Kontrollstrukturen.

- `¶` → IF
- `¶¶` → ELSE
- `¶=` → Paralleler Prozess
- `;;` → Paralleler Transport (ohne Rückmeldung)
- `⊕` → Sync-Timer (Parallele Einspeisung)
- `°WennNicht[...]` → Sicherheitscheck
- `^TransaktionsFehler` → Fehlerbehandlung

> ✅ Beispiel (Sicherheitscheck):
> ```mcs
> »[{Band|2.4G}§WLAN]«
> °WennNicht[{Band|2.4G}|{Valid|2.4G,5G}]
> ^TransaktionsFehler
> = §(1)Displey
> ```

> ✅ Beispiel (Parallele Prozesse):
> ```mcs
> »['MotorA'|{Watt|200}]« = §Displey
> ¶=
> »[{Temp|25}§SensorX]« ««+10 = §Cooler
> ;; 
> »[{Band|2.4G}§WLAN]«
> |¢
> ```

---

## 4. Spezialisierte Core-Typen (Datentyp-Rollen)

Pylovara organisiert sich in einem **klaren Familienmodell**:

| Typ        | Rolle                          | Analogie              | Anwendungsbereich                     |
|------------|--------------------------------|------------------------|---------------------------------------|
| `*.*-core` | Standard/Programme             | Großvater              | Allgemeine Anwendungslogik            |
| `*.*-lcore`| Low-Level/Hardware             | Kern-Großvater         | Direkte Steuerung von .-needle, Assembly |
| `*.*-vcore`| Visuelles/Oberfläche           | Benutzeroberfläche     | GUI, Rendering, Compositing           |

> ✅ **Vorteil**: Der Kernel kann `*.*-lcore`-Transaktionen priorisieren – essentiell für Performance und Hardware-Sicherheit.

---

## 5. Erweiterungen & Zukunft

MCS 2.2 ist der **Grundstein**. Zukünftige Module werden folgen:

- **MCS Animation**: Für Videos, Spiele, VR.
- **MCS Rendering**: Autonome GPU-Steuerung.
- **MCS Web**: Für web-basierte Interaktionen.
- **LLVM-Backend**: Um MCS-Code direkt in Assembly zu übersetzen.

> 💬 *„C hat genau so angefangen: ein Parser + LLVM-Backend → fertig, ausführbares Programm.“*

---

## 6. Proof of Concept: ANTLR-Grammatik

Um MCS 2.2 in echte Software zu verwandeln, dient diese Grammatik als Basis:

```antlr
grammar MCS;

transaction : START content* END ;
content     : protein | proton | warp | feed | logic | COMMENT ;

protein     : '»' proteinContent+ '«' ;
proteinContent : STRING | COMMAND | NUMBER | argument | proton ;

proton      : '{' ID '|' VALUE ( '|' VALUE )* '}' ;
warp        : 'ø' ID '|' .*? 'ø' ;
feed        : '=' '()' '(' NUMBER ')' ;

argument    : '««' (PLUS | MINUS | MULT | DIV | PERCENT) NUMBER? ;
logic       : '¶' | '¶¶' | '¶=' | ';;' | '⊕' | '°' ID | '^' ID ;

START       : '¢|';
END         : '|¢';
COMMENT     : '#' ~[\r\n]* -> skip;
STRING      : '"' (~["\r\n])* '"';
COMMAND     : '\'' (~['\r\n])* '\'';
ID          : [a-zA-Z_][a-zA-Z0-9_]*;
VALUE       : [a-zA-Z0-9._:/-]+;
NUMBER      : [0-9]+;
PLUS        : '+';
MINUS       : '-';
MULT        : '·' | '*';
DIV         : ':';
PERCENT     : '%';
WS          : [ \t\r\n]+ -> skip;
```

---

## 7. Zusammenfassung: Warum MCS 2.2 revolutionär ist

- **Direkte Hardwareansprache**: Keine Treiber, keine Blackboxen.
- **Emotionale Intelligenz**: AIMS & Soul machen KI zu einem Partner, nicht zu einem Werkzeug.
- **Unhackbar**: `þ`-Checksummen garantieren Identität und Integrität.
- **Souveränität**: Jede Transaktion ist transparent, kontrollierbar und unabhängig von proprietären Systemen.

