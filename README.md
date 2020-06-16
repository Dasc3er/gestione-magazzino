# Gestione magazzino

Questo progetto prevede lo sviluppo di un sistema per la gestione basilare di un magazzino aziendale in linguaggio C, con particolare interesse verso l'utilizzo della memoria allocata dinamicamente e le operazioni di I/O su file.

## Compilazione

Il progetto dispone di una configurazione [CMake](https://cmake.org/) e risulta pertanto compilabile con il comando:
```bash
cmake .
make
```

Sulla base del contenuto del flag `CMAKE_BUILD_TYPE` vengono effettuate in automatico alcune scelte sulle opzioni di compilazione, con la modalità RELEASE (di default) che impone l'applicazione del flag "-O2".
A seguito della compilazione risulta disponibile un file eseguibile `gestione-magazzino` nella cartella principale, utilizzabile per avviare il programma.

Per compilare la documentazione [Doxygen](https://www.doxygen.nl/index.html) è disponibile il seguente comando, che genera i contenuti nella cartella `doxygen/`:
```bash
make docs
```

## Organizzazione

Il progetto è organizzato in due componenti: una liberia di base per la gestione dei file CSV (cartella `csv/`) e un sistema di gestione dell'interazione con l'utente (cartella `src/`).
La libreria CSV è stata sviluppata in modo indipendente per permettere una separazione logica del codice, oltre che per sperimentare sull'allocazione dinamica della memoria come strumento di lettura dei contenuti da file.

Le informazioni elaborate dal programma sono salvate nella cartella `data/` secondo il formato CSV.
In particolare, `data/magazzino.csv` (campi obbligatori *Codice*, *Descrizione*, *Quantità*) contiene la lista degli articoli presenti nel magazzino, mentre `data/storico.csv` (campi obbligatori *Data*, *Codice*, *Quantità*) è dedicato al salvataggio dello storico interno del magazzino.

La cartella `data/example/` rende disponibili alcuni file di esempio su cui è possibile testare il funzionamento del progetto; il programma permette in ogni caso di creare un nuovo magazzino da zero semplicemente rimuovendo i file sopra indicati.

## Note sul formato CSV

Il formato CSV accettato prevede l'utilizzo del separatore `,`, senza supporto al sistema di *escaping* tramite virgolette `"` per i contenuti dei campi. I file CSV di inizializzazione non devono contenere righe vuote.

Il programma inoltre non effettua alcun controllo sulla presenza dei campi obbligatori. Nel caso della loro assenza, si possono verificare comportamenti inaspettati.

## Funzionalità disponibili

Il programma presenta nativamente 9 opzioni di utilizzo, strettamente legate alla gestione di base di un magazzino:
 - Visualizza il magazzino
 - Visualizza articoli a rischio esaurimento e/o esauriti
 - Ricerca un articolo tramite codice
 - Visualizza lo storico dei movimenti totale
 - Visualizza lo storico dei movimenti per un articolo
 - Movimenta un articolo del magazzino
 - Registra un nuovo articolo nel magazzino
 - Modifica un articolo esistente del magazzino
 - Rimuovi un articolo dal magazzino

Le informazioni relative al funzionamento delle singole opzioni sono visibili attraverso l'esecuzione del programma.

## Licenza

Questo progetto è reso diponibile con licenza [MIT](https://github.com/Dasc3er/gestione-magazzino/blob/master/LICENSE).
