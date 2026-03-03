### Geplante Statistiken
## Zur Veranschaulichung der geplanten Auswertungen wurden Beispieldateien erstellt, die das vorgesehene Ausgabeformat demonstrieren.

## Laufende Statistiken (pro Zeitschritt):
Nach jedem Zeitschritt werden im Terminal die aktuellen Simulationsdaten ausgegeben. Diese umfassen:

    -Zeit: aktueller Zeitschritt der Simulation.

    -Belegung: Anzahl der aktuell belegten Stellplätze.

    -Auslastung: prozentualer Anteil belegter Stellplätze bezogen auf die Gesamtkapazität.

    -Neu: Anzahl neu angekommener Fahrzeuge im aktuellen Zeitschritt.

    -Verlassen: Anzahl der Fahrzeuge, die das Parkhaus im aktuellen Zeitschritt verlassen haben.

    -Wartende rein: Anzahl der Fahrzeuge, die aus der Warteschlange einen freien Stellplatz erhalten haben.

    -Belegungsänderung: Differenz der Belegung zum vorherigen Zeitschritt (Belegung(t) − Belegung(t−1)); positiver Wert zeigt eine Aufbauphase, 0 eine Sättigungsphase  und ein negativer Wert eine Entlastungsphase.

    -Warteschlange: Anzahl der aktuell vor dem Parkhaus wartenden Fahrzeuge.

    -Ø Restparkdauer: Durchschnitt der verbleibenden Parkdauer aller parkenden Fahrzeuge; dient als Indikator für die erwartbare zeitliche Entwicklung der Belegung.


Diese Informationen dienen der unmittelbaren Beobachtung des Verkehrsflusses sowie der Entwicklung von Belegung und Warteschlange.
Parallel dazu werden dieselben Daten strukturiert in einer Textdatei tabellarisch gespeichert, um eine bessere Übersicht und spätere Analyse zu ermöglichen.

## Endstatistiken (nach Abschluss der Simulation)
Nach Beendigung der Simulation werden zusammenfassende Kennzahlen sowohl im Terminal als auch in der Textdatei ausgegeben.
Folgende Kennwerte werden berechnet:

    -Anteil Zeitschritte mit Vollauslastung: Prozentualer Anteil der Zeitschritte, in denen alle Stellplätze belegt waren.

    -Durchschnittliche Belegung: Mittlere Anzahl belegter Stellplätze über die gesamte Simulation im Verhältnis zur Gesamtkapazität.

    -Durchschnittliche Auslastung: Durchschnittliche prozentuale Auslastung des Parkhauses.

    -Maximale Warteschlangenlänge: Höchste Anzahl gleichzeitig wartender Fahrzeuge.

    -Durchschnittliche Warteschlangenlänge: Mittlere Anzahl wartender Fahrzeuge über alle Zeitschritte.

    -Durchschnittliche Restparkdauer: Mittlere verbleibende Parkdauer aller parkenden Fahrzeuge.

    -Geschätzte zusätzliche Stellplätze: Abschätzung der zusätzlich benötigten Kapazität zur Reduzierung von Warteschlangen.

Diese Endstatistiken ermöglichen eine Bewertung der Kapazitätsauslastung, der Verkehrsbelastung sowie möglicher Engpässe des Parkhauses.


## Beispiel 
    Simulation Parkhaus Rauenegg
--------------------------------------------------------------------------------------------------------------------------
    Zeit | Belegung | Auslastung | Neu | Verlassen | Wartende rein | Belegungsänderung | Warteschlange | durch. Restparkdauer
    --------------------------------------------------------------------------------------------------------------------------
      0 |        0 |      0.00% |   0 |         0 |             0 |                0  |             0 |             0.0
      1 |        3 |     30.00% |   3 |         0 |             0 |               +3  |             0 |             6.0
      2 |        5 |     50.00% |   2 |         0 |             0 |               +2  |             0 |             6.5
      3 |        7 |     70.00% |   2 |         0 |             0 |               +2  |             0 |             7.0
      4 |        9 |     90.00% |   2 |         0 |             0 |               +2  |             1 |             7.2
      5 |       10 |    100.00% |   3 |         2 |             2 |               +1  |             3 |             5.8
      6 |       10 |    100.00% |   1 |         1 |             1 |                0  |             3 |             5.0
      7 |        9 |     90.00% |   1 |         2 |             0 |               -1  |             2 |             4.2
      8 |        8 |     80.00% |   1 |         2 |             0 |               -1  |             1 |             3.5
      9 |        6 |     60.00% |   0 |         2 |             0 |               -2  |             0 |             2.8
     ...|      ... |        ... | ... |       ... |           ... |              ...  |           ... |             ...
    --------------------------------------------------------------------------------------------------------------------------

    
    Endstatistik
    -------------------------------------------------------------------
    Anteil Zeitschritte mit Vollauslastung:         20.0 %
    Durchschnittliche Belegung:                     6.7 / 10
    Durchschnittliche Auslastung:                   67.0 %
    Maximale Warteschlangenlaenge:                  3 Fahrzeuge
    Durchschnittliche Warteschlangenlaenge:         1.0 Fahrzeuge
    Durchschnittliche Restparkdauer:                4.8 Zeitschritte
    Geschaetzte zusaetzliche Stellplaetze:          3
    -------------------------------------------------------------------