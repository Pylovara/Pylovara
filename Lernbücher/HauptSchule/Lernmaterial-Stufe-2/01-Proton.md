# Kapitel 1: Das Proton (Zustandssteuerung)

Willkommen in der nächsten Stufe deiner Ausbildung als Entwickler! 🌟

Du hast bereits gelernt, wie man mit dem **Transaktionsrahmen** `¢! ... !¢` (unserem früheren "Zauberrand") einen sicheren Bereich schafft und wie der **Arbeitsflächenprozess** (Meister REX) dort die Workspaces aufstellt. Du kennst auch schon die **Proteine** `[]` (die großen Zauberkisten), in denen wir unsere Daten speichern.

Heute gehen wir einen Schritt tiefer in die Logik. Stell dir vor, du hast ein Objekt in deinem Protein – zum Beispiel einen Affen 🐒. Dieser Affe braucht Informationen oder Zustände, die direkt zu ihm gehören, wie zum Beispiel sein Futter oder seine Energie.

Dafür nutzen wir das **Proton**. Wir nennen es ab jetzt auch **Zustands-Container** oder kleine Kiste.

---

## Das Symbol für das Proton: {}

Das Proton wird durch geschweifte Klammern dargestellt. Es umschließt spezifische Werte, die einem Objekt zugeordnet werden:

# {}

## Objekte mit Zuständen versorgen

Um einem Objekt (im Protein) Informationen mitzugeben, setzen wir das Proton einfach mit hinein. Wir trennen die Bereiche wie gewohnt mit dem **Trennbefehl** `|`.

Schau dir die Struktur an:

### »["Affe" | {"Bananen"}]«

Hier ist der Affe das Haupt-Datenpaket, und in seinem Proton `{}` trägt er die Information über seine Nahrung mit sich. 🍌

Oder für mehrere Informationen:

### »["Hund" | {"Hundefutter"} | {"Ball"}]«

Hier hat das Objekt "Hund" zwei Protons: Eines für seine Nahrung und eines für seinen aktuellen Zustand (er möchte spielen).

---

## Statische Daten vs. Aktive Ausführung

Wichtig ist die Unterscheidung, ob Daten nur gespeichert sind oder gerade verarbeitet werden. Dafür nutzen wir den **Aktionsdraht** `» ... «`:

- `["Affe" | {"Bananen"}]` – Das ist ein **schlafendes Protein**. Es liegt im Speicher bereit, aber es passiert noch nichts.
- `»["Affe" | {"Bananen"}]«` – Hier ist der Aktionsdraht aktiv. Das System verarbeitet die Daten jetzt – der Affe wird gefüttert!

---

## Übung: Prozess-Ströme erstellen

Versuche, die folgenden Abläufe im Transaktionsrahmen zu verstehen:

```text
¢!
»["Hund" | {"Komm her"}]«
 ¬· »["Essen" | {"Hundefutter"}]« 
     # Der Hund isst und wechselt danach in den Spielmodus
     ¬· »["Ball" | {"Renn zum Ball"}]«
     ¬· »["Kuscheltier" | {"Kuschel dich an mich"}]«
!¢
```

```text
¢!
»["Katze" | {"Komm her"}]«
 ¬· »["Milch" | {"Trink die Milch"}]« 
     # Die Katze trinkt und sucht sich einen Beschäftigung
     ¬· »["Kratzbaum" | {"Kratz den Baum"}]«
     ¬· »["Spielzeugmaus" | {"Spiel mit der Maus"}]«
!¢
```

---

### Deine Aufgaben:

1. **Struktur zeichnen:** Erstelle ein Protein `[]` für einen Hund 🐕.
2. **Proton hinzufügen:** Zeichne ein Proton `{}` in das Protein und schreibe "Knochen" hinein. Vergiss den Trennbefehl `|` nicht!
3. **Syntax schreiben:** Schreibe die vollständige Zeile für einen schlafenden Hund mit seinem Knochen auf.
   *(Tipp: `["Hund" | {"Knochen"}]`)*

---

> [!TIP]
> **Für Eltern & Lehrkräfte:** Das **Proton** `{}` dient in der Pylovara-Architektur der Definition von **Attributen** und **Hardware-Zuständen**. Während das Protein den Container für ein Objekt definiert, liefert das Proton die Parameter (z.B. Spannungswerte, Farben oder Mengen), die für die Hardware-Steuerung (Gatter/Register) benötigt werden.
> - Helfen Sie dem Lernenden zu verstehen, dass `{}` immer etwas beschreibt oder versorgt, was im `[]` definiert wurde.
