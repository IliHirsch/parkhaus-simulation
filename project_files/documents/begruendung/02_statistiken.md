# Begründungstext: Übersicht zu den geplanten Statistiken

## Zielsetzung
Ziel der geplanten Statistiken ist es, den Ablauf der Parkhaus‑Simulation nachvollziehbar zu machen und gleichzeitig Kennzahlen zu liefern, mit denen sich Auslastung, Warteschlangenbildung und typische Zeiten (Parkdauer/Wartezeit) bewerten lassen. Die Statistiken sind so gewählt, dass sie direkt aus dem aktuellen Simulationszustand (Parkhaus + Warteschlange) berechnet werden können und die wichtigsten Effekte sichtbar machen:
- **Kapazitätsauslastung** (Belegung/Queue),
- **Dynamik pro Zeitschritt** (Neu/Verlassen/Queue→Park),
- **zeitliche Kenngrößen** (Parkdauer, Wartezeit, Restparkdauer‑Samples).

## Bezug zum aktuellen Programmaufbau
Die Simulation arbeitet in diskreten Zeitschritten. Pro Step werden:
1. Abfahrten verarbeitet,
2. ggf. ein neues Fahrzeug erzeugt (max. 1 Ankunft pro Step gemäß Zufallsereignis),
3. die Warteschlange abgearbeitet (FIFO, solange Plätze frei sind),
4. anschließend werden Statistiken aktualisiert und ausgegeben bzw. geloggt.

Damit sind sowohl **Step‑Werte** (für kurzfristige Beobachtung) als auch **Aggregate** (für Endauswertung) sinnvoll und direkt aus den im Code vorhandenen Datenstrukturen ableitbar (`ParkingLot`, `Queue`, `Stats`).

## Laufende Statistiken pro Zeitschritt (Konsole + Log-Kernwerte)
Folgende Step‑Kennzahlen werden pro Zeitschritt geführt und ausgegeben:

- **Zeit/Step**: aktueller Zeitschritt der Simulation.
- **Belegung**: Anzahl belegter Stellplätze nach dem Step (`Stats.belegung`, aus `ParkingLot.belegte_plaetze`).
- **Warteschlange**: Anzahl wartender Fahrzeuge nach dem Step (`Stats.warteschlangenlaenge`, aus `Queue.size`).
- **Neu angekommen**: Anzahl neu erzeugter Fahrzeuge in diesem Step (`Stats.neu_angekommen`).
- **Verlassen**: Anzahl abgefahrener Fahrzeuge in diesem Step (`Stats.verlassen`).
- **Queue→Park**: Anzahl Fahrzeuge, die aus der Warteschlange eingeparkt wurden (`Stats.abgefertigte_wartende`).

Optional (falls im Ausgabeformat vorgesehen) kann zusätzlich ein Restparkdauer‑Wert ausgegeben werden (siehe nächster Abschnitt).

### Hinweis zur „Ø Restparkdauer“
Im aktuellen Statistikmodell werden Restparkdauern als **Samples** gesammelt: In jedem Step werden die Restparkdauern **aller aktuell parkenden Fahrzeuge** zur Summe addiert und der Sample‑Zähler erhöht. Dadurch entsteht ein **kumulativer Durchschnitt über alle bisher gesammelten Restparkdauer‑Samples**:
- `sum_restparkdauer / count_restparkdauer`

Das ist **kein reiner Step‑Durchschnitt des aktuellen Zustands**, sondern ein Durchschnitt über den Verlauf der Simulation bis zu diesem Zeitpunkt (Sample‑basiert). Diese Definition ist absichtlich so gewählt, weil sie robust ist und ohne zusätzliche temporäre Variablen auskommt.

## Endstatistiken nach Abschluss der Simulation (Konsole + Log)
Nach Ende der Simulation werden zusammenfassende Kennzahlen berechnet, die eine Bewertung von Auslastung und Warteschlangenbildung ermöglichen:

- **Anteil Zeitschritte mit Vollauslastung**: `vollauslastung_steps / step_count` (in %).
- **Durchschnittliche Belegung**: `sum_belegung / step_count` (als Anzahl Stellplätze).
- **Durchschnittliche Warteschlangenlänge**: `sum_warteschlange / step_count`.
- **Maximale Warteschlangenlänge**: `max_warteschlange`.
- **Durchschnittliche Wartezeit (Queue→Park)**: `sum_wartezeit / count_wartezeit` (nur wenn Samples existieren).
- **Durchschnittliche Parkdauer (bei Ankunft gezogen)**: `sum_parkdauer / count_parkdauer`.
- **Durchschnittliche Restparkdauer (Sample‑basiert, optional)**: `sum_restparkdauer / count_restparkdauer` (falls im Ausgabeformat ausgegeben).

## Warum diese Auswahl sinnvoll ist
- Die Step‑Werte machen den Ablauf transparent (wann Fahrzeuge ankommen/abfahren und ob sich die Queue aufbaut).
- Die Aggregate erlauben eine belastbare Bewertung über die gesamte Simulationsdauer, ohne dass einzelne Zufallsschwankungen dominieren.
- Wartezeit wird nur dort gemessen, wo sie inhaltlich korrekt ist: **nur wenn ein Fahrzeug tatsächlich aus der Queue eingeparkt wird** (Queue→Park‑Ereignis).
- Parkdauer wird direkt bei der Fahrzeugerzeugung erfasst und bildet damit die zugrundeliegende Nachfrage/Last der Simulation ab.

## Abgrenzung (was bewusst nicht als feste Statistik zugesichert wird)
Kennwerte wie **prozentuale Auslastung**, **Belegungsänderung** oder **Anteil Wartezeit an Gesamtzeit** sind mit dem aktuellen `Stats`‑Layout nicht als verpflichtende Ausgabewerte implementiert. Solche Werte können zwar später ergänzt werden, werden in der Abgabe jedoch nur dann genannt, wenn sie im tatsächlichen Ausgabecode auch berechnet und ausgegeben werden.
