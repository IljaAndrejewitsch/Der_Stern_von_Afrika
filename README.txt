Prüfungsaufgabe C/C++ SoSe 2020
Budnikov Ilia
Hochschule Emden/Leer
Informatik

-> Programm „Der Stern von Afrika“
Die Idee des Programms wurde durch den Roman „Der Südstern oder Das Land der Diamanten“ von Jules Verne (1884) inspiriert.
Der Diamant aus dem Roman hat einen echten Prototyp - den Diamanten „Stern von Südafrika“, auch „Dudley Diamond“, der 1869 am Ufer des Oranje-Flusses gefunden wurde.

Das Programm ist als Brettspiel konzipiert.

Alle genutzten Topics sind im Quelltext, auch in der „build.sh“-Datei, bezeichnet. Diese wurden mit einem Kommentar „Topic“ bzw. „Topic optional“ versehen. Mehrere Themen werden im Programmcode einmal in bemerkenswerten Fällen hervorgehoben, weil ihre Anzahl zu umfangreich ist (z.B. Datentypen, Abstraktionen, Bitmuster, Best Practices und manche anderen Themen). Insgesamt wurden alle 28 Topics im Programm behandelt. Als „Topic optional“ werden Topics bezeichnet, die in Materialpaketen erwähnt und in diesem Programm verwendet wurden, aber sich nicht in der Liste von Themen der Aufgabestellung befinden.

Das Programm beinhaltet kurze Zeitverzögerungen, um die Textfragmente voneinander besser zu trennen. Es ist nicht notwendig zu versuchen, die Informationen, die auf dem Bildschirm erscheinen, während der vorgesehenen Zeit zu lesen. Etwas Wichtiges kann man im Programm nicht übersehen.
Die Delays führen dazu, dass es für Nutzer möglich ist, während einer Zeitverzögerung einzugeben. Infolgedessen entstehen keine Probleme mit dem Programmablauf, aber mit der nächsten Eingabe kann ein Nutzer eine Meldung bekommen, dass der eingegebene Wert falsch ist, da der alte eingelesen wurde. Das lässt sich nur mit großen Anstrengungen lösen, weil in dem Fall die Eingabe nicht unbedingt mit dem newline character, '\n' , enden soll.

!!! für MX-Linux gilt:
Die Größe des Terminals sollte für ein optimales Gameplay mindestens 88x33 mit der Normalgröße des Texts (s. Rechtsklick, Größenänderung) sein. Ansonsten kann (im schlimmsten Fall) die Afrika-Landkarte nicht ganz korrekt angezeigt werden, können Textzeilen wegen der ungünstigen Umbrüche vermischt oder manche Spielfelder in der Legende ausgelassen werden. Mit screen-sized Terminal und angehnemer Textgröße ist es am besten, gerne können Sie experimentieren.


-> Fileorganisation
In der zip-Archivdatei „Der_Stern_von_Afrika“ befinden sich:
  o  build.sh             File, Build des Programms
  o  README.txt           File, Hauptinformationen
  o  classdiagram.pdf     File, Klassendiagramm
  o  src                  Verzeichnis mit cpp-Dateien
  o  include              Verzeichnis mit hpp-Dateien


-> Building & Ausführen
Das Programms kann mit der „build.sh“-Datei, die in demselben Ordner (Ort) mit dieser README-Datei liegt, gebildet werden. Um das Spiel zu starten, soll man die nach dem Builden im demselben Ordner erzeugte „DerSternVonAfrika.out“-Datei ausführen.
Das Spiel lässt sich während des Spielablaufs beenden: im Abschnitt „Andere Moeglichkeiten“ unter der Nummer 5 „Spiel beenden“.


-> Regeln
Hier werden die Hauptpunkte des Spiels beschrieben, detailliertere Informationen können während des Spiels oder durch das Durchlesen bestimmter Codefragmente gewonnen werden.
Der Code ist nicht so „open-closed“, wie er sein könnte. Das liegt teilweise daran, dass die Gewichtung der Grundregeln, ursprünglich festgelegten Regeln, lieber nicht geändert werden sollte, um das Gleichgewicht nicht zu stören.
An dem können von 1 bis 4 Spielern teilnehmen.

Während des Spiels wird das Wesentlichste klar, Regeln sollten bei Bedarf gelesen werden.

--> Spielziel
Um zu gewinnen, muss einer der Spieler den Diamanten in Besitz nehmen und ihn nach Tanger oder Kairo bringen.

--> Währung
Die Währung ist darauf ausgelegt, sich auf dem Spielfeld zu bewegen. Diese wird von der Bank verwaltet. Spieler verfügen auch über das Geld. Dieses wird von der Bank während des Spiels verteilt.
  o  Scheine von 100 – 19 Stk. 
  o  Scheine von 500 – 8  Stk.

--> Spielfeld
Das Spielfeld ist eine Landkarte von Afrika, auf der die bemerkenswerten Orte des Kontinents Afrika eingezeichnet sind. Diese Orte sind Spielfelder. Jede Feldnummer auf der Karte ist einem Ort in der Legende eindeutig zugeordnet. Spieler beginnen das Spiel in Tanger oder Kairo (wahlweise) und begeben sich auf die Suche nach dem Diamanten. Zwischen den Spielfeldern sind Routen ausgelegt. Eine Route kann weiß, blau oder rot sein. Die Farben zeichnen jeweilige Bewegungsmöglichkeiten aus (s. unten im Abschnitt „Bewegung“).
Der Spieler, der am schnellsten nach Kapstadt gekommen ist, erhält 500 Geld.

--> Bewegung
Spieler bewegen sich auf dem Spielbrett abwechselnd. Um die Anzahl von Schritten zu ermitteln, soll ein Spieler würfeln. Aufgrund der geringen Größe des Spielfeldes beschränkt sich diese Anzahl auf 3 (1-3).
Es ist möglich, zu Lande (weiße Routen), zu Wasser (blaue Routen) oder in der Luft (rote Routen) auf dem Spielbrett zu reisen. Zu Lande ist es kostenlos, zu Wasser 100, in der Luft 300 Geld. Einem Spieler werden nur die Bewegungsmöglichkeiten angeboten, die sein Budget nicht überschreiten. Wenn einem Spieler das Geld ausgeht und es keine Möglichkeit gibt, an Land zu ziehen, dann gibt die Bank dem Spieler den erforderlichen Geldbetrag (falls verfügbar). Wenn die Bank nicht genug Geld hat, um zu helfen, oder wenn der Spieler die Hilfe bereits genutzt hat, verliert er. Wenn alle Spieler verloren haben, ist das Spiel beendet.
Hinweis:
Der Bewegungsprozess hat ein absichtlich kompliziertes Verfahren, bei jedem Schritt den nächsten Ort auf der Karte zu finden (auszuwählen). Die Nummern in der Liste der verfügbaren Reiseziele während der Auswahl stimmen nicht mit den Nummern überein, die den Orten auf der Karte zugeordnet sind. Dies trägt dazu bei, dass afrikanische Länder, Städte, bemerkenswerte Orte mit der Zeit gelernt werden und der Richtungssinn verbessert wird. Sonst würden nur Zahlen im Laufe des Spielt beachtet werden.

--> Arten von Spielern
Standardspieler (Player) spielt nach den Grundregeln, beginnt das Spiel mit der Summe von 300 Geld.
Seemann (Sailor) bewegt sich kostenlos auf dem Wasser, hat aber ursprünglich 100 Geld.
Sportler (Sportsman) erhält einen zusätzlichen Schritt zur Gesamtanzahl der Schritte. Dieser Spielertyp beginnt das Spiel mit einem leeren Portemonnaie.
Reiche (RichMan) bekommt zu Beginn des Spiels 800 Geld. Der Spielertyp geht jedoch immer einen Schritt weniger. Bei der Schrittanzahl 1 bleibt der Reiche einfach stehen.

--> Sonderaktionen
Sonderaktionen stellen Ereignisse dar, die mehrmals pro Spiel nach dem Zufallsprinzip auf dem Spielbrett verteilt werden. Einem Feld wird also eine Sonderaktion zugeordnet. Einige Felder, darunter Tanger, Kairo und Kapstadt, bleiben nach der Verteilung leer, ohne Sonderaktionen. Wenn die Aktion ausgelöst wird, verschwindet sie aus dem Brett. Die Verteilung findet zu Beginn des Spiels statt, danach wenn alle Sonderaktionen wurden ausgelöst (aber der Diamant muss dabei nicht unbedingt gefunden werden) oder wenn der Diamant gefunden wurde. Der Diamant wird nur zu Beginn des Spiels versteckt, bei der nächsten Verteilung ändert sich sein Standort nicht mehr. Der Spieler löst während seines Zuges auf jedem passierten Feld (bei jedem Schritt) eine Sonderaktion aus, falls vorhanden.
Mögliche Sonderaktionen:
Während eines Zuges kann ein Spieler einen Edelstein finden und dafür eine Belohnung erhalten, in eine Falle geraten, einen Wegelagerer treffen und das ganze Geld verlieren (und den Diamanten, der dann in Kapstadt platziert wird). Außerdem ist es möglich, dass ein Spieler von der afrikanischen Natur fasziniert wird und somit den Zug früher als geplant beendet. Wenn ein Spieler von Sklavenhändlern gefangen genommen wird, muss der Spieler drei Schritte auf seinem Platz bleiben. In diesem Fall bleiben das Geld und der Diamant bei dem Spieler.

--> Finden des Diamanten
Ein Spieler, der den Diamanten findet, muss ihn so schnell wie möglich nach Tanger oder Kairo bringen. Alle anderen Spieler werden zu Räubern und erhalten für jeden Zug einen Extraschritt. Jeder Typ behält dabei seine Vorteile. Ein Sportler-Räuber macht zum Beispiel zwei Extraschritte.
Es ist wichtig zu beachten, dass Sie den Diamanten nicht sofort zurücknehmen können, wenn ein anderer Spieler den Diamanten gerade von Ihnen genommen hat und auf Ihrem eigenen Feld geblieben ist (Sie müssen mindestens zwei Schritte machen, genauer gesagt auf das andere Feld und zurück). Außerdem kann ein Spieler-Räuber einen Diamantträger in Tanger oder Kairo nicht einfach erwarten. Sobald der Diamant eine dieser Städte erreicht, gewinnt der Spieler sofort, der ihn mitgebracht hat.
 

-> Programmstruktur
Hier werden Klassendiagramm des Programms und kurze Beschreibungen jeder Diagrammkomponente angeführt. Methoden, die zu keiner Klasse gehören (free-standing), werden auf dem Diagramm als statische Methoden einer im Kontext am besten passenden Klasse oder als eine einzelne Klasse dargestellt. Einfache Getter- und Setter-Methoden wurden nicht erwähnt, um das Diagramm übersichtlich zu halten.

s. Klassendiagramm in der pdf-Datei mit dem Namen „classdiagram“

Die Reihenfolge der Klassenbeschreibungen entspricht dem intuitiven Lesen des Diagramms: von oben nach unten, von links nach rechts.
--> AnsiConsole wird für die Grafik verwendet.
--> Color ist eine Enumeration, die verfügbare Grafikfarben darstellt und dadurch einen schnelleren und einfacheren Zugriff auf die Farben ermöglicht.
--> Checkinput beihaltet die Methode „checkInput(...)“, die die Robustheit des Spiels zu erhöhen hilft. Mit dieser lässt sich jede Eingabe der Nutzer prüfen und somit ein korrektes Eigabenergebnis erzielen.
--> DataTypeInput ist eine Enumeration, die alle zu prüfenden Eingabetypen beinhaltet: Integer-Zahlen, PascalString-Text und Morsecode.
--> println vereinfacht die Ausgabe.
--> MorseCodeParser wird für das Entziffern von Morsecodeeingaben der Nutzer. Somit wird geprüft, ob das eingegebene Wort einem von gültigen Mustern entspricht.
--> PascalString wird für die Darstellung vom Text im Programm verwendet. Die Mehrheit der Klassen hat einen PascalString als Attribut, und die resultierenden Beziehungen sind klar. Um das Diagramm übersichtlich zu halten, wurden diese Assoziationen nicht explizit gezeichnet.
--> ColoredShape repräsentiert eine abstrakte farbige Figur und fordert die Subklassen eine Methode zu implementieren, die die von ihnen dargestellten Figuren zeichnet.
--> Circle erbt von der Klasse ColoredShape, repräsentiert einen Kreis. Wird verwendet, um die Spielfelder auf der Karte zu markieren.
--> Line erbt von der Klasse ColoredShape, repräsentiert eine Linie. Damit werden Begrüßung, Spielergebnisse, Routen und Ränder gezeichnet.
--> Position ist die Lage der Figuren im Koordinatensystem auf dem Brettspiel (Afrika-Landkarte).
--> Space stellt ein Spielfeld dar. Es gibt insgesamt 24 Felder auf dem Spielbrett.
--> Spaces ist eine Enumeration, die alle im Spiel beteiligten Orte des Kontinents Afrika erfasst.
--> WayToReach ist eine Enumeration, die die Reisemöglichkeiten zwischen Spielfeldern erfasst.
--> Board ist die Hauptklasse des Spiels. Diese repräsentiert die Abstraktion des Spielbretts (bspw. sammelt Felder, ordnet Sonderaktionen (spezial actions) jedem Feld zu). Über diese Klasse wird der Spielprozess verwaltet, z.B. Bewegung und Wechsel der Spieler.
Diese Klasse wurde als Entwurfsmuster „singleton“ umgesetzt. Sie beinhaltet bedeutende Methoden und Attribute, die von mehreren Objekten anderer Klassen zugegriffen werden sollen. Das Brettspiel darf aber nur in einem Exemplar existieren, was zur Einbeziehung dieses Entwurfsmuster führt.
--> main beihalet die Methode „main()“, die für das Starten des Spiels und Setzen des Seeds für die Zufallszahlengenerierung verwendet wird.
--> PlayerFactory ist ein konkreter Erzeuger in Bezug auf das Entwurfsmuster „factory method“. Diese Fabrik erzeugt einen Spieler von einem bestimmten Typ abhängig von der Wahl eines Nutzers. Beschreibung jedes Typs wird bei der Auswahl am Anfang des Spiel gezeigt.
--> Types ist eine Enumeration, die alle Spielertypen beinhaltet.
--> Player stellt nicht nur die Abstraktion eines Spielers dar, sondern auch den Standardtyp, also ist die Klasse nicht abstrakt und kann instanziiert werden. Interagiert mit dem Interface State durch die Delegation der Methodenaufrufe an den aktuellen Zustand.
--> RichMan (Reiche), Sailor (Seemann) und Sportsman (Sportler) erben von der Klasse Player und somit erweitern den Standardtyp.
--> State ist ein Interface, woran ein Objekt der Klasse Player manche Methodenaufrufe delegiert. Dieses Interface definiert somit die Schnittstelle zwischen einem Spieler und seinen konkreten Zuständen. Da das Verhalten eines Spielers stark vom jeweiligen Zustand abhängt, entspricht die Organisation und Implementierung der Zustandsklassen dem Entwurfsmuster „state“.
--> DefaultState ist ein konkreter Zustand, in dem sich alle Spieler befinden, wenn der Diamant zu keinem Spieler gehört.
--> RichManDefaultState erweitern den DefaultState entsprechend für den Typ RichMan. Ein Spieler dieses Typs muss einen Schritt bei jedem Zug weniger machen, was dazu führt, dass der Spieler manchmal während des Zugs stehenbleiben muss. Diese Situation sollte einzeln behandelt werden.
--> WithDiamondState ist ein konkreter Zustand, in den der Spieler versetzt wird, der den Diamanten gefunden hat. Alle anderen Spieler werden dann in den Zustand RobberState versetzt. Nach dem Einholen des Spielers mit dem Diamanten bekommt der Eingeholte den Zustand RobberState und der neue Diamantträger den Zustand WithDiamondState.
--> Bank ist für das Währungsmanagement notwendig. Wird als das Entwurfsmuster „singleton“ im Spiel umgesetzt, da es nur eine Bank existieren darf. Außerdem muss man im Spiel sehr oft mit der Bank interagieren, deswegen ist eine flexible und sichere Implementierung einer Klasse mit einer einzelnen Instanz ist von Bedeutung, was genau dieses Entwurfsmuster gewährleistet.
--> Banknote stellt die Spielwährungseinheit dar. Ein Objekt der Klasse kann einen Wert von 100 oder 500 haben.
