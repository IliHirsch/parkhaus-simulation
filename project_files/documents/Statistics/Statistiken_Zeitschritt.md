# Statistiken pro Zeitschritt (Definitionen und Berechnung)

Dieses Dokument beschreibt die Kennwerte, die nach jedem Zeitschritt ausgegeben werden, und wie sie aus den aktuellen Datenstrukturen berechnet werden.

---

## 1. Zeitschritt

**Definition:**  
Laufender Zähler des aktuellen Simulationsschritts.

**Quelle:**  
Parameter `step` in der Simulation / Ausgabefunktion.

---

## 2. Belegung

**Definition:**  
Anzahl belegter Stellplätze nach Abschluss des Zeitschritts.

**Quelle / Berechnung:**  
`belegung = ParkingLot.belegte_plaetze`  
Wird in `stats_update_step()` als `Stats.belegung` gespeichert.

---

## 3. Warteschlangenlänge

**Definition:**  
Anzahl wartender Fahrzeuge (FIFO-Queue) nach Abschluss des Zeitschritts.

**Quelle / Berechnung:**  
`warteschlangenlaenge = queue_size(Queue)`  
Wird in `stats_update_step()` als `Stats.warteschlangenlaenge` gespeichert.

---

## 4. Neu angekommene Fahrzeuge

**Definition:**  
Anzahl Fahrzeuge, die im aktuellen Zeitschritt neu erzeugt wurden (egal ob direkt eingeparkt oder in die Queue gestellt).

**Quelle:**  
Step-Zähler `Stats.neu_angekommen` (wird bei `parking_handle_arrival()` erhöht).

---

## 5. Fahrzeuge verlassen

**Definition:**  
Anzahl Fahrzeuge, die im aktuellen Zeitschritt das Parkhaus verlassen haben, weil ihre Restparkdauer auf 0 (oder kleiner) gefallen ist.

**Quelle:**  
Step-Zähler `Stats.verlassen` (wird in `parking_process_departures()` erhöht).

---

## 6. Abgefertigte Wartende (Queue → Park)

**Definition:**  
Anzahl Fahrzeuge, die im aktuellen Zeitschritt aus der Warteschlange entnommen und eingeparkt wurden.

**Quelle:**  
Step-Zähler `Stats.abgefertigte_wartende` (wird in `parking_process_queue()` erhöht).

---

## 7. Ø Restparkdauer (kumulativ)

**Definition:**  
Durchschnitt der verbleibenden Restparkdauern über **alle bisher gesammelten Samples**.

**Wichtig:**  
In der aktuellen Datenstruktur ist dies **kein „nur aktueller Zeitschritt“-Durchschnitt**, sondern ein kumulativer Durchschnitt über die gesamte bisherige Laufzeit.

**Quelle / Berechnung:**  
Samples werden pro Zeitschritt für jedes parkende Fahrzeug gesammelt:  
- `sum_restparkdauer += fahrzeug.restparkdauer`  
- `count_restparkdauer += 1`  

Dann:  
`avg_restparkdauer = sum_restparkdauer / count_restparkdauer` (falls `count_restparkdauer > 0`)

---

## Ausgabehinweis

Die laufenden Kennwerte werden sowohl auf der Konsole als auch in einer Log-Datei ausgegeben.  
Die Log-Datei enthält die gleichen Werte, damit sie später einfach ausgewertet werden kann.
