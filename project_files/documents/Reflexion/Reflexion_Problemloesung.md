# Erklärung und Reflexion des Projekts

## Lösung der Aufgabenstellung

Unser Ziel war es, die Parkhaus-Simulation übersichtlich, modular und gut erweiterbar umzusetzen. Die Simulation basiert auf diskreten Zeitschritten, in denen Fahrzeuge mit einer bestimmten Wahrscheinlichkeit ankommen, im Parkhaus parken und dieses nach Ablauf ihrer Parkdauer wieder verlassen.
Zur Umsetzung haben wir das Parkhaus als feste Anzahl von Stellplätzen modelliert. Fahrzeuge werden als eigene Datenstruktur mit ID, verbleibender Parkdauer und Einfahrtszeitpunkt dargestellt. Falls keine Stellplätze frei sind, werden Fahrzeuge in einer dynamisch verwalteten Warteschlange gespeichert. Die Parkdauer sowie die Ankunft von Fahrzeugen werden mithilfe eines Zufallszahlengenerators bestimmt.
Zur besseren Strukturierung des Projekts haben wir eine klare Ordnerstruktur mit „documents“, „include“, „src“ und „tests“ gewählt. Dadurch ist schnell ersichtlich, wo sich welche Bestandteile befinden.

## Diskutierte Alternativen und Begründung der Entscheidung

Im Team haben wir verschiedene Ansätze zur Modularisierung diskutiert. Eine Alternative war es, die Funktionalität stärker zu bündeln, beispielsweise in den Header-Dateien „parking“, „stats“, „queue“, „simulation“ und „types“.
Dem gegenüber stand unser gewählter Ansatz mit einer feineren Aufteilung in „config“, „io“, „parking“, „queue“, „rng“, „simulation“, „stats“ und „types“.

Wir haben uns für die feinere Modularisierung entschieden, da diese eine klarere Trennung der Verantwortlichkeiten ermöglicht. Einzelne Komponenten wie Zufallszahlengenerierung oder Ein-/Ausgabe sind dadurch unabhängig voneinander und leichter testbar.
Außerdem verbessert diese Struktur die Wartbarkeit und Erweiterbarkeit des Programms, da Änderungen gezielt in einzelnen Modulen vorgenommen werden können, ohne andere Bereiche zu beeinflussen.

## Herausforderungen in der Zusammenarbeit

Eine Schwierigkeit bestand darin, dass wir zu Beginn keine Pull Requests verwendet haben, sondern Änderungen direkt über die Bash in den Main-Branch gemergt haben. Dadurch waren Änderungen sofort im Remote-Repository sichtbar, ohne zuvor ein Review durch andere Teammitglieder zu durchlaufen.
Dies hat die Qualitätssicherung erschwert, da Feedback nur indirekt über das Kanban-Board und Issues erfolgen konnte. Im Verlauf des Projekts haben wir erkannt, dass Pull Requests eine strukturiertere Zusammenarbeit ermöglichen.

## Positive Aspekte der Teamarbeit

Besonders positiv war die Bereitschaft im Team, eigene Ideen zugunsten besserer Lösungen zurückzustellen. Dadurch konnten wir auch bei unterschiedlichen Meinungen schnell zu gemeinsamen Entscheidungen kommen.
Dies hat es uns ermöglicht, effizient weiterzuarbeiten, auch unter Zeitdruck, und Konflikte konstruktiv zu lösen.