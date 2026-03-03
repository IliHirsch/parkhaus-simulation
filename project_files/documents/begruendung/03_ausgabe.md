# Begründungstext: Format der geplanten Ausgabe (Konsolenausgabe + Log-Datei) mit Testdaten

## Zielsetzung
Das Ausgabeformat soll zwei Anforderungen gleichzeitig erfüllen:
1. **Direkte Nachvollziehbarkeit während der Simulation** (Konsole): Pro Zeitschritt sieht man, was passiert.
2. **Dokumentation und spätere Analyse** (Log-Datei): Dieselben Kernwerte werden strukturiert gespeichert, damit die Ergebnisse auch nachträglich geprüft und ausgewertet werden können.

## Geplantes Ausgabeformat in der Konsole
Während der Simulation wird pro Zeitschritt eine kompakte Zeile ausgegeben. Das Format orientiert sich an den im Code vorhandenen Step‑Kennzahlen:

- Step (Zeit)
- Belegung
- Warteschlange
- Neu angekommen
- Verlassen
- Queue→Park (aus Warteschlange eingeparkt)

Optional kann zusätzlich ein Restparkdauer‑Wert ausgegeben werden. Dabei ist zu beachten:
- Wenn „Ø Restparkdauer“ ausgegeben wird, ist dies im aktuellen Modell ein **kumulativer Sample‑Durchschnitt** über alle bisherigen Restparkdauer‑Samples.

Dieses Format ist bewusst kurz gehalten, damit man auch bei langen Simulationen den Verlauf schnell erfassen kann.

## Geplantes Ausgabeformat in einer Log-Datei (Textdatei)
Parallel zur Konsole wird eine Log-Datei geschrieben, um die wichtigsten Werte pro Step dauerhaft zu speichern. Die Log-Datei enthält einen **strukturierten Kern‑Datensatz** pro Step, der 1:1 aus den `Stats`‑Feldern stammt, z. B.:

- Step
- neu (Neu angekommen)
- verlassen
- queue→park
- belegung
- queue (Warteschlangenlänge)

Optional kann zusätzlich ein Restparkdauer‑Wert (`AvgRest`) geloggt werden, wenn entsprechende Samples vorhanden sind.

### Wichtiger Hinweis zur Übereinstimmung Konsole vs. Log
Die Log-Datei ist nicht zwingend eine exakte Kopie der Konsolenanzeige, sondern ein **tabellarischer Kern‑Auszug**. Dadurch bleibt das Log stabil, gut parsbar und auf die tatsächlich gespeicherten Werte begrenzt.

## Ausgabe am Ende der Simulation (Konsole + Log)
Nach Abschluss der Simulation werden die Endstatistiken ausgegeben und zusätzlich geloggt. Dazu zählen insbesondere:
- Anteil Zeitschritte mit Vollauslastung
- Ø Belegung
- Ø Warteschlangenlänge
- maximale Warteschlangenlänge
- Ø Wartezeit (Queue→Park, nur bei vorhandenen Samples)
- Ø Parkdauer (bei Ankunft gezogen)
- optional: Ø Restparkdauer (Sample‑basiert)

Diese Zusammenfassung ist nötig, um die Simulationsergebnisse ohne manuelle Nachrechnung bewerten zu können.

## Testdaten und Beispieldateien
Zur Veranschaulichung werden Beispieldateien bereitgestellt, die das geplante Layout demonstrieren:
- Beispielausgabe pro Zeitschritt (Konsole)
- Beispielausgabe am Ende (Konsole)
- geplantes Log-Format (Textdatei)

Die Beispielwerte dienen nur der Illustration des Formats; die konkreten Zahlen hängen vom gewählten Seed, den Parametern und den Zufallsereignissen ab.

## Begründung der Formatwahl
- **Konsole**: schnell, übersichtlich, ideal zum Debuggen und zum direkten Verständnis des Ablaufs.
- **Log-Datei**: reproduzierbar, gut archiviert, ermöglicht spätere Auswertung (z. B. per Skript/Excel) ohne erneutes Durchlaufen der Simulation.
- Trennung in Step‑Ausgabe und Endausgabe reduziert Informationsüberflutung und hält die Simulation live lesbar.
