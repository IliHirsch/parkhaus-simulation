# Ausgabeformat der geplanten Statistiken

Dieses Dokument beschreibt **welche Kennwerte ausgegeben werden** und **wie sie aus den im Programm verwendeten Datenstrukturen entstehen**.  
Die Formulierungen und Berechnungen sind auf den aktuellen Stand der Header/Strukturen (`types.h`, `stats.h`, `io.h`) abgestimmt.

---

## 1. Laufende Statistiken pro Zeitschritt (Terminal + Log-Datei)

Nach jedem Zeitschritt werden die wichtigsten Zustands- und Step-Zähler ausgegeben.  
Die Werte stammen aus der `Stats`-Struktur **nach** `stats_update_step()`.

### Ausgegeben werden:

- **Zeitschritt (`step`)**  
  Der aktuelle Zeitschritt der Simulation (Parameter der Ausgabefunktion).

- **Belegung (`belegung`)**  
  Anzahl der belegten Stellplätze **nach Abschluss** des Zeitschritts.  
  Quelle: `Stats.belegung` (wird aus `ParkingLot.belegte_plaetze` übernommen).

- **Warteschlangenlänge (`warteschlangenlaenge`)**  
  Anzahl wartender Fahrzeuge **nach Abschluss** des Zeitschritts.  
  Quelle: `Stats.warteschlangenlaenge` (wird über `queue_size()` ermittelt).

- **Neu (`neu_angekommen`)**  
  Anzahl neu erzeugter Fahrzeuge im aktuellen Zeitschritt (unabhängig davon, ob direkt eingeparkt oder in die Queue gestellt).  
  Quelle: Step-Zähler `Stats.neu_angekommen` (wird im Ankunftsmodul erhöht).

- **Verlassen (`verlassen`)**  
  Anzahl Fahrzeuge, die im aktuellen Zeitschritt das Parkhaus verlassen haben.  
  Quelle: Step-Zähler `Stats.verlassen` (wird im Abfahrtsmodul erhöht).

- **Wartende rein (`abgefertigte_wartende`)**  
  Anzahl Fahrzeuge, die im aktuellen Zeitschritt aus der Queue in einen freien Stellplatz eingeparkt wurden.  
  Quelle: Step-Zähler `Stats.abgefertigte_wartende` (wird beim Abarbeiten der Queue erhöht).

- **Ø Restparkdauer (kumulativ)**  
  Durchschnitt der verbleibenden Restparkdauern **über alle bisher gesammelten Samples**.  
  Wichtig: Diese Größe ist in der aktuellen Struktur **kumulativ**, nicht „nur für den aktuellen Zeitschritt“.  
  Quelle: `Stats.sum_restparkdauer / Stats.count_restparkdauer` (Samples werden in `stats_update_step()` gesammelt).

### Zweck
Die laufende Ausgabe dient dazu, den Verlauf der Simulation (Belegung, Stau vor dem Parkhaus, Abflüsse) Schritt für Schritt nachvollziehen zu können.  
Parallel wird die gleiche Information in eine Log-Datei geschrieben, um sie später auszuwerten.

---

## 2. Endstatistiken nach Abschluss der Simulation (Terminal + Log-Datei)

Am Ende der Simulation werden aggregierte Kennzahlen ausgegeben. Alle Werte sind aus der `Stats`-Struktur berechenbar.

### Ausgegeben werden:

- **Anteil Zeitschritte mit Vollauslastung [%]**  
  Prozentualer Anteil der Zeitschritte, in denen das Parkhaus voll war.  
  Berechnung: `(vollauslastung_steps * 100.0) / step_count`

- **Durchschnittliche Belegung**  
  Mittlere Anzahl belegter Stellplätze über alle Zeitschritte.  
  Berechnung: `sum_belegung / step_count`

- **Durchschnittliche Warteschlangenlänge**  
  Mittlere Queue-Länge über alle Zeitschritte.  
  Berechnung: `sum_warteschlange / step_count`

- **Maximale Warteschlangenlänge**  
  Größte gemessene Queue-Länge während der Simulation.  
  Quelle: `max_warteschlange`

- **Durchschnittliche Wartezeit (Queue → Park)**  
  Mittlere Wartezeit der Fahrzeuge, die **tatsächlich** aus der Queue eingeparkt wurden.  
  Berechnung: `sum_wartezeit / count_wartezeit` (falls `count_wartezeit > 0`)

- **Durchschnittliche geplante Parkdauer**  
  Mittlere (bei Ankunft gezogene) Parkdauer aller erzeugten Fahrzeuge.  
  Berechnung: `sum_parkdauer / count_parkdauer` (falls `count_parkdauer > 0`)

- **Durchschnittliche Restparkdauer (Samples)**  
  Mittlere Restparkdauer über alle gesammelten Samples (aus allen Zeitschritten, über alle parkenden Fahrzeuge).  
  Berechnung: `sum_restparkdauer / count_restparkdauer` (falls `count_restparkdauer > 0`)

### Hinweis zu nicht enthaltenen Kennwerten
Kennwerte wie **Auslastung in %**, **Belegungsänderung ΔBelegung** oder **„geschätzte zusätzliche Stellplätze“** werden in der aktuellen Struktur nicht direkt geführt bzw. lassen sich mit den aktuellen Funktionssignaturen nicht sauber ohne zusätzliche Parameter/State ausgeben.  
Für die Abgabe werden daher nur Kennwerte aufgeführt, die mit der vorhandenen Datenhaltung konsistent berechenbar sind.
