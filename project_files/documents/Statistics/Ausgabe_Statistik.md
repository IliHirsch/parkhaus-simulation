# Format der geplanten Ausgabe

## 1. Allgemeines Ausgabeformat

Die Simulation verwendet eine strukturierte **Konsolenausgabe**, die
parallel in eine Log-Datei geschrieben wird. Das gewählte Format ist
textbasiert, da:

-   es plattformunabhängig ist,
-   keine zusätzlichen Bibliotheken benötigt werden,
-   es leicht nachvollziehbar und prüfbar ist,
-   und es exakt den internen Datenstrukturen (`Stats`, `ParkingLot`,
    `Queue`) entspricht.

Es werden zwei Ebenen der Ausgabe unterschieden:

1.  Laufende Statistik pro Zeitschritt\
2.  Abschlussstatistik nach Ende der Simulation

Die Werte stammen ausschließlich aus der zentralen `Stats`-Struktur.

------------------------------------------------------------------------

## 2. Laufende Ausgabe pro Zeitschritt

Nach jedem Simulationsschritt wird eine kompakte Statuszeile ausgegeben.

### Struktur der Ausgabe:

    Step <n>: Belegung=<x>, Queue=<y>, Neu=<a>, Verlassen=<b>, Queue->Park=<c>, AvgRest=<d>

### Bedeutung der Werte:

-   **Step**: Aktueller Zeitschritt
-   **Belegung**: Anzahl belegter Stellplätze nach dem Schritt
-   **Queue**: Anzahl wartender Fahrzeuge
-   **Neu**: Neu angekommene Fahrzeuge im Schritt
-   **Verlassen**: Fahrzeuge, die das Parkhaus verlassen haben
-   **Queue-\>Park**: Fahrzeuge, die aus der Warteschlange eingeparkt
    wurden
-   **AvgRest**: Durchschnittliche Restparkdauer (kumulativ über alle
    Samples)

Diese Darstellung erlaubt eine klare Analyse des Systemverhaltens im
Zeitverlauf.

------------------------------------------------------------------------

## 3. Abschlussausgabe (Endstatistiken)

Nach Abschluss aller Zeitschritte werden aggregierte Kennzahlen
ausgegeben.

### Struktur der Ausgabe:

    ===== FINAL STATS =====
    Ø Belegung: <x>
    Ø Warteschlange: <y>
    Max Warteschlange: <z>
    Vollauslastung: <p> % der Schritte
    Ø Wartezeit (Queue->Park): <w>
    Ø Parkdauer: <k>
    Ø Restparkdauer (Samples): <r>

### Berechnungsgrundlagen:

-   Durchschnittswerte werden als Summe / Anzahl berechnet.
-   Prozentwerte basieren auf der Anzahl Vollauslastungs-Schritte.
-   Wartezeit berücksichtigt nur Fahrzeuge, die tatsächlich eingeparkt
    wurden.
-   Restparkdauer basiert auf allen während der Simulation gesammelten
    Samples.

------------------------------------------------------------------------

## 4. Beispielausgabe mit Testdaten

### Testparameter:

-   Stellplätze: 5\
-   Max. Parkdauer: 3\
-   Simulationsdauer: 5 Schritte\
-   Ankunftswahrscheinlichkeit: 100 %\
-   Seed: 1

### Beispiel Konsolenausgabe:

    Step 0: Belegung=1, Queue=0, Neu=1, Verlassen=0, Queue->Park=0, AvgRest=3
    Step 1: Belegung=2, Queue=0, Neu=1, Verlassen=0, Queue->Park=0, AvgRest=2
    Step 2: Belegung=3, Queue=0, Neu=1, Verlassen=0, Queue->Park=0, AvgRest=2
    Step 3: Belegung=3, Queue=1, Neu=1, Verlassen=1, Queue->Park=1, AvgRest=1
    Step 4: Belegung=3, Queue=2, Neu=1, Verlassen=1, Queue->Park=1, AvgRest=1

    ===== FINAL STATS =====
    Ø Belegung: 2
    Ø Warteschlange: 0
    Max Warteschlange: 2
    Vollauslastung: 0 % der Schritte
    Ø Wartezeit (Queue->Park): 1
    Ø Parkdauer: 2
    Ø Restparkdauer (Samples): 2

Die Zahlen dienen der Illustration des Formats und zeigen, dass sowohl
Verlauf als auch Endzustand nachvollziehbar dokumentiert werden.

------------------------------------------------------------------------

## 5. Zusammenfassung

Das gewählte Ausgabeformat erfüllt folgende Anforderungen:

-   klare Trennung zwischen Step- und Endstatistik\
-   vollständige Rückführbarkeit auf interne Datenstrukturen\
-   reproduzierbare Testausgabe durch festen Seed\
-   automatische Dokumentation in einer Log-Datei\
-   direkte Prüfbarkeit im Terminal

Damit ist der Aufgabenpunkt „Format der geplanten Ausgabe mit Testdaten"
vollständig erfüllt.
