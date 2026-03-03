# Statistiken am Ende der Simulation (Definitionen und Berechnung)

Dieses Dokument beschreibt die Kennwerte, die nach Abschluss der Simulation ausgegeben werden, und wie sie aus der `Stats`-Struktur berechnet werden.

---

## 1. Anteil Zeitschritte mit Vollauslastung [%]

**Definition:**  
Prozentualer Anteil der Zeitschritte, in denen das Parkhaus vollständig ausgelastet war.

**Quelle / Berechnung:**  
`vollauslastung_prozent = (vollauslastung_steps * 100.0) / step_count`

Voraussetzung: `step_count > 0`

---

## 2. Durchschnittliche Belegung

**Definition:**  
Mittlere Anzahl belegter Stellplätze über alle simulierten Zeitschritte.

**Quelle / Berechnung:**  
`avg_belegung = sum_belegung / step_count`

Voraussetzung: `step_count > 0`

---

## 3. Durchschnittliche Warteschlangenlänge

**Definition:**  
Mittlere Anzahl wartender Fahrzeuge (Queue-Länge) über alle simulierten Zeitschritte.

**Quelle / Berechnung:**  
`avg_queue = sum_warteschlange / step_count`

Voraussetzung: `step_count > 0`

---

## 4. Maximale Warteschlangenlänge

**Definition:**  
Größte Warteschlangenlänge, die während der Simulation beobachtet wurde.

**Quelle:**  
`max_warteschlange` (wird während der Simulation fortgeschrieben).

---

## 5. Durchschnittliche Wartezeit (Queue → Park)

**Definition:**  
Mittlere Wartezeit der Fahrzeuge, die aus der Warteschlange entnommen und eingeparkt wurden.  
Die Wartezeit ist definiert als:  
`wartezeit = aktueller_step - einfahrtzeit`

**Quelle / Berechnung:**  
`avg_wartezeit = sum_wartezeit / count_wartezeit`

Voraussetzung: `count_wartezeit > 0`  
Wenn keine Fahrzeuge aus der Queue eingeparkt wurden, ist die Kennzahl nicht aussagekräftig und kann als „0 Samples“ ausgegeben werden.

---

## 6. Durchschnittliche geplante Parkdauer

**Definition:**  
Mittlere Parkdauer, die bei der Erzeugung eines Fahrzeugs zufällig gezogen wurde.

**Quelle / Berechnung:**  
`avg_parkdauer = sum_parkdauer / count_parkdauer`

Voraussetzung: `count_parkdauer > 0`

---

## 7. Durchschnittliche Restparkdauer (Samples)

**Definition:**  
Mittlere verbleibende Restparkdauer über alle gesammelten Samples.  
Ein Sample ist ein parkendes Fahrzeug in einem Zeitschritt.

**Quelle / Berechnung:**  
`avg_restparkdauer = sum_restparkdauer / count_restparkdauer`

Voraussetzung: `count_restparkdauer > 0`
