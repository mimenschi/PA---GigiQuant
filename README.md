Acest program prelucreaza date economice pentru 4 scenarii diferite.

Scenariul 1: Se da un fisier cu numarul de observatii si preturile fiecaruia iar dupa se calculeaza sharpe ratio, randamentul si volatilitatea portofoliului.

Scenariul 2: In fisierul de intrare se afla numele a 3 orase urmate de preturile din anumite zile. Programul analizeaza returile si iti afiseaza ziua si orasul in care poti profita de arbitraj.

Scenariul 3: Se dau numele a 10 companii si preturile stockurilor lor pe timp de mai multe zile (minim 3). Programul afiseaza ce companii se pot pune perechi pentru a balansa portfoliul.

Scenariul 4: Ca si date de intrare se da numarul de observatii, pretul start, target si dimensiunea intervalului iar programul calculeaza lantul markov al acestor date.

Date despre proiect:

In fisierul src se gasesc fisierele cu functii pentru fiecare scenariu alaturi de headerul lor si fisierul sursa intitulat "test.c" in care se ruleaza progarmul in sine. 

Programul este scris astfel incat sa intre in scenarii in functie de numele fisierului. Astfel pentru a putea rula corect programul apelul se face in felul urmator:

./nume.exe fisierNR.in fisierNR.out

Abordarea fisierelor in functie de numar se face astfel:

Intre 1 si 5: Scenariul 1

Intre 6 si 10: Scenariul 2

Intre 11 si 15: Scenariul 3

Intre 16 si 20: Scenariul 4

Pentru a modifica functiile care prelucreaza datele la un anume scenariu se poate intra in fisierul ftaskNR.c unde NR reprezinta numarul scenariului.

Imbunatatiri:

La momentul de fata programul nu afiseaza corect datele pentru scenariul 3. Se poate intra in functia vectorFrunze pentru a imbunatati crearea vectorului de frunze si respectiv in functia afisarePerechi2 pentru a verifica metoda de afisare.
