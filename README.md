# Gestione magazzino

Questo progetto prevede lo sviluppo di un sistema per la gestione basilare di un magazzino aziendale in linguaggio C, con particolare interesse verso l'utilizzo della memoria dinamica e delle operazioni di I/O su file.

## Compilazione

Il progetto dispone di una configurazione [CMake](https://cmake.org/) e risulta pertanto compilabile con il comando:
```bash
cmake .
make
```

Sulla base del contenuro del flag CMAKE_BUILD_TYPE vengono effettuate in automatico alcune scelte sulle opzioni di compilazione.
La compilazione in modalità RELEASE impone l'applicazione del flag "-O2".

Per compilare la documentazione [Doxygen](https://www.doxygen.nl/index.html) è disponibile il seguente comando, che genera i contenuti nella cartella `doxygen/`
```bash
make docs
```

## Organizzazione

Il progetto è organizzato in due componenti differenti: una liberia di base per la gestione dei file CSV (cartella `csv/`) e un sistema di gestione dell'interazione con l'utente (cartella `src/`).

Le informazioni elaborate dal programma sono salvate nella cartella `data/` secondo il formato CSV, con separazione dei campi tramite `,`.
In particolare, `data/magazzino.csv` contiene la lista degli articolo presenti nel magazzino mentre `data/storico.csv` è dedicato al salvataggio dello storico interno del magazzino.

La cartella `data/example/` rende disponibili alcuni file di esempio su cui è possibile testare il funzionamento del progetto; il programma permette in ogni caso di creare un nuovo magazzino da zero semplicemente rimuovendo i file sopra indicati.

## Utilizzo

Il programma presenta nativamente 8 opzioni di utilizzo.

## Licenza

Questo progetto è reso diponibile con licenza [MIT](https://github.com/Dasc3er/gestione-magazzino/blob/master/LICENSE).
