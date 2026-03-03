# Funktionsprototypen mit einheitlichem Header

## Ziel der Funktionsprototypen

Alle geplanten Funktionen der Simulation sind in den jeweiligen
Header-Dateien (`.h`) als Funktionsprototypen deklariert.

Ziel dieser Vorgehensweise ist:

-   klare Definition der Schnittstellen zwischen Modulen,
-   frühzeitige Festlegung der Parameter und Rückgabewerte,
-   Trennung von **Schnittstelle** und **Implementierung**,
-   bessere Nachvollziehbarkeit für andere Entwickler und Prüfer.

Die Header-Dateien enthalten ausschließlich die Prototypen und
Dokumentationskommentare, während die Implementierung bzw. der
Pseudocode in den `.c`-Dateien erfolgt.

------------------------------------------------------------------------

## Einheitlicher Aufbau der Funktionsheader

Alle Funktionen folgen einem einheitlichen Dokumentationsschema mit:

-   `@brief` → kurze Funktionsbeschreibung
-   Beschreibung des Funktionszwecks
-   `@param[in]`, `@param[out]`, `@param[in,out]` → klare
    Parameterkennzeichnung
-   `@return` → Rückgabewertbeschreibung

Beispielstruktur:

``` c
/**
 * @brief Kurzbeschreibung der Funktion.
 *
 * Detailliertere Erklärung des Ablaufs oder Zwecks.
 *
 * @param[in]  param1 Beschreibung
 * @param[out] param2 Beschreibung
 * @return Beschreibung des Rückgabewerts
 */
ReturnType function_name(Type param1, Type* param2);
```

------------------------------------------------------------------------

## Begründung für die einheitliche Struktur

### 1. Klare Schnittstellen zwischen Modulen

Durch die Prototypen in den Header-Dateien ist eindeutig definiert:

-   Welche Daten ein Modul benötigt
-   Welche Daten es verändert
-   Welche Werte es zurückliefert

Dadurch entsteht ein klarer Datenfluss und die Module bleiben sauber
entkoppelt.

------------------------------------------------------------------------

### 2. Vermeidung von Implementierungsabhängigkeiten

Andere Module sehen nur:

-   Datentypen
-   Funktionssignaturen

Nicht jedoch:

-   interne Variablen
-   konkrete Implementierungsdetails
-   Speicherverwaltung im Inneren

Das reduziert Kopplung und erhöht Wartbarkeit.

------------------------------------------------------------------------

### 3. Explizite Kennzeichnung der Parameterrollen

Durch die Verwendung von:

-   `@param[in]`
-   `@param[out]`
-   `@param[in,out]`

wird klar dokumentiert:

-   welche Parameter nur gelesen werden,
-   welche verändert werden,
-   welche als Ergebniscontainer dienen.

Dies verhindert typische Fehler wie:

-   unbeabsichtigte Veränderung von Daten,
-   falsche Übergabe per Wert statt per Referenz,
-   Missverständnisse über Zustandsänderungen.

------------------------------------------------------------------------

### 4. Konsistenz über alle Module hinweg

Alle Module (`config`, `simulation`, `parking`, `queue`, `stats`, `io`,
`rng`) verwenden denselben Aufbau.

Beispiele:

-   `bool config_validate(const SimConfig* cfg);`
-   `SimStatus parking_handle_arrival(...);`
-   `void stats_update_step(...);`
-   `bool queue_push(Queue* q, Vehicle v);`

Die Signaturen sind bewusst so gewählt, dass:

-   Zustände über Zeiger übergeben werden,
-   Strukturen nicht unnötig kopiert werden,
-   Änderungen explizit sichtbar sind.

------------------------------------------------------------------------

### 5. Vorbereitung auf spätere Implementierung

Da Teil 1 des Projekts noch kein vollständiges lauffähiges Programm
erfordert, dienen die Prototypen als formale Planung der Architektur.

Sie ermöglichen:

-   strukturierten Programmentwurf,
-   klare Zuordnung von Verantwortlichkeiten,
-   direkte Umsetzung in Teil 2 ohne strukturelle Änderungen.

------------------------------------------------------------------------

## Zusammenfassung

Die Funktionsprototypen bilden die vertraglich festgelegten
Schnittstellen zwischen den Modulen der Simulation.

Durch:

-   einheitliche Dokumentation,
-   klare Parameterkennzeichnung,
-   saubere Trennung von Header und Implementierung,

wird eine strukturierte, nachvollziehbare und wartbare Architektur
geschaffen.

Die gewählte Struktur unterstützt sowohl die Anforderungen der
Aufgabenstellung als auch eine spätere vollständige Implementierung der
Simulation.
