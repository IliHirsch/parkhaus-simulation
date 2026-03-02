#ifndef VEHICLE_H
#define VEHICLE_H

/**
 * @brief Struktur zur Darstellung eines Fahrzeugs.
 *
 * Ein Fahrzeug besitzt eine eindeutige ID,
 * eine verbleibende Parkdauer sowie
 * den Zeitpunkt der Einfahrt.
 */

typedef struct
{
    int id;
    int remaining_parking_time;
    int arrival_time;
} vehicle_t;

/**
 * @brief Erstellt und initialisiert ein Fahrzeug.
 *
 * @param[in] id Eindeutige Fahrzeug-ID
 * @param[in] parking_time Anfangs-Parkdauer
 * @param[in] arrival_time Zeitpunkt der Einfahrt
 * @return Initialisierte Fahrzeugstruktur
 */

vehicle_t vehicle_create(int id,
                         int parking_time,
                         int arrival_time);

/**
 * @brief Reduziert die verbleibende Parkdauer um einen Zeitschritt.
 *
 * @param[in,out] p_vehicle Zeiger auf Fahrzeug
 */

void vehicle_decrement_time(vehicle_t *p_vehicle);

#endif /* VEHICLE_H */