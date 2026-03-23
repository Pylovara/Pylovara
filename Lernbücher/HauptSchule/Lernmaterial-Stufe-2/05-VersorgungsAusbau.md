## Kapitel 5 VersorgungsAusbau

Hallo kleiner Zauber Entwickler! 🌟

Nach dem wir gelernt haben das wir 
Unseren zauber Versorgen müssen, werden wir
mit den Kleinen Zauberkisten(Proton) die Versorgung
Ausbauen.

Jetzt lassen wir unsere Gegenstände und Tiere in 
Schlafenden Zauberkisten mit Versorgung schlafen,
um mit der Versorgung Händisch auszubauen.

Solange wir die Versorgung nicht Händisch geben
oder die Zauberkisten nicht Ausbauen, werden sie
schlafen und nicht Aktiv sein.

solange das so ist wird in jeder Zauberkiste
die Versorgungskiste mit geführt.


# 1. Die Versorgung Ausbauen

Vieleicht hat unser Hund Hunger und Durst
 oder Eben nicht - Das ist die Frage die wir uns
 stellen müssen.

 Wer kann Entscheidungszauber ausführen ?

 Zwischen Frage: 

und wer stellt die Arbeitstische her ?

 Zwischen Frage:

#########################################################

 Und Jetzt bauen wir den Wenn-Nein Entscheidungszauber aus
 und setzen sie Richtig:

¢!

 ["Hund"|{"Futter"|"Wasser"}]
 ¶ ¬· »["FutterNapf Holen"|{"Futter"}]«
       ¬· »["Mit der Hand Futter Füllen"|{"Futter"}]«
           ¬· »["FutterNapf ist Voll"]«

   ¬· »["WasserNapf Holen"|{"Wasser"}]« 
       ¬· »["Mit der Hand Wasser Füllen"|{"Wasser"}]«
           ¬· »["WasserNapf ist Voll"]«

 ¶¶ ¬· 




!¢



Mögliche Lösung: ["Hund schlafen lassen"|{"Futter"|"Wasser"}]



###########################################################