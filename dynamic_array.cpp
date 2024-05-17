#include <cstdlib>
#include <time.h>
#include <iostream>
template <typename T> class DynamicArray // zdefinowanie klasy jako szablon 
{
    private:
        int size;   //ilosc elementow w tej talbicy
        int capacity;   //wielkosc fizyczna tablicy
        T* array = NULL;    //utworznuie zmiennej array i przypisanie jej od razu wartosc NULL 

    public:
        DynamicArray()  //lista inicjalizacyjna array(nullptr) jest tak zapobiegawczo i moze zostac pominiety
        {
            capacity = 1;   //dajemy rozmiar tablicy by w ogole moc ja stworzyc
            size = 0;   //nie mamy jeszcze zadnych elementow zatem nasz rozmiar bedzie rony 0
            array = new T[capacity];    //zaalokowanie nowej tablicy array o type T
            srand(time(0)); // Zaainicjopwanie randomowej wartosci
        }
       
        int getSize(){return size;} // funkcja zwraca rozmiar talblicy

        int getCapasity(){return capacity;} // funckja zwraca pojhemnosc talbicy

        void push_back(T value)  //funckja ma za zadanie wlozyc na ostatnie miejsce listy, element o wartosci przez nas zdefinowanej i pozniej zwieksza jej rozmiar 
        {
            grow_array();
            array[size] = value; // przypisujemy na mijescu size nasza wartosc ktora uzywamy
            size++; // zwiekszamy rozmiar talbicy tym razem w samej zmiennej
        }
        
        void pop_back() //funckja majaca na celu ,,wyrzucenie ostatniego elemtnetu z tablicy"
        {
            if (size != 0)
            {
                array[size-1] = T(); //przyrownujemy wartosc ostatniego elementu talbicy do wartosc 0.
                //T() to yrazenie ktore tworzy nowy obiekt typu T przy uzyciu konstruktora domyslnego a wartosc domylsna to jest 0
                shrink_array();
                size--; // pomnijeszenie rozmiary talbicy o jeden
            }
        }

        void Find(){ // Funkcja wyszukująca losową liczbę w liście

            for (int i = 0; i < size; i++) {
                if(array[i] == 18){
                    break;
                };
            }
        }

        void push_front(T value) 
        {
            grow_array(); // Jeśli chcesz zwiększyć rozmiar tablicy, zakładam, że masz na to swoje przesłanki.

            // Przesuwamy wszystkie elementy tablicy o jeden indeks w prawo, zaczynając od ostatniego elementu.
            for (int i = size; i > 0; i--) {
                array[i] = array[i - 1];
            }

            // Wstawiamy nową wartość na początek tablicy.
            array[0] = value;

            // Zwiększamy rozmiar tablicy.
            size++;
        }


        void pop_front() 
        {
        if (size != 0) {
            shrink_array(); // Jeśli chcesz zmniejszyć rozmiar tablicy, zakładam, że masz na to swoje przesłanki.

            // Przesuwamy wszystkie elementy tablicy o jeden indeks w lewo, zaczynając od drugiego elementu do przedostatniego.
            for (int i = 0; i < size - 1; i++) {
                array[i] = array[i + 1];
            }

            // Ostatni element tablicy zostaje skasowany.
            array[size - 1] = T(); // Ustawiamy ostatni element na domyślną wartość typu T.
            
            // Zmniejszamy rozmiar tablicy.
            size--;
        }
        }


        void push_random(T value)
        {
            grow_array();// sprawdzenie czy mozna ppowikszyc array
            if(size == 0)// Jesli lista jest pusta
            {
                array[0] = value; // To pipisujemy nowa watyosc (value) do pierwszego miejsca w tablicy
            }else{
                int rand = std::rand() % size; // Generownaie liczby randomowej
                for (int i = size; i > rand; i--)// Przesuniecie wszystkich wartosci na prawo (od miejsca gdzie damy nowa wartosc)  
                {
                    array[i] = array[i-1];
                }
                array[rand] = value;// Przypisanie w miejscu rand nowej wartosci
            }
            size++;// Zwiekszenie rozmiaru o jeden
        }

        void pop_random()
        {
            if (size != 0) // Sprawdzenie czy lista jest pusta
            {
                shrink_array();// Sprawdzenie czy mozna zmniejszyc tablice
                int rand = std::rand() % size; // Generowanie liczby randomowej
                for (int i = rand; i < size-1; i++) // Przesuniecie wszystkich wartosci na prawo od naszego miejsca rand w lewo o jedno miejsce
                {
                    array[i] = array[i+1];
                }
                size--;// Zmnnijeszenie rozmiaru tablict
            }
        }

        void grow_array() // funckja sprawdzajaca czy mozna ziwekszysc rozmiar tablicy jezeli tak robi to
        {
            if (size == capacity) // jezeli rozmiar tablicy jest rowny jej pojemnosci 
            {
                T* newlist = new T[capacity*2];  //tworzymy nowa liste o dwa razy wieskzym rozmiarze 
                capacity = capacity*2; //tutaj zwiekszamy pojemnosc listy dwukrotnie ale tym razem samej zmiennej
                for(int i=0;i<size;i++) // petla ktora bedzie iterowac tyle razy jaki jest rozmiar listy (ile jest tam jej elementow)
                {
                    newlist[i] = array[i];  // wartosci ze starej listy zapisujemy do nowej listy przez nas stworzonej
                }
                delete[] array; // usuwamy stara liste z pamieci
                array = newlist; // przypisujemy nowa liste do starej nazwwy tej zmiennej
            } else {
                return; // jezeli nie trzeba to wychodzimy z funckji
            }
        }

        void shrink_array() // funkcja sprawdzajaca czy mozna zmniejszyc rozmiar tablicy
        {
            if (size == capacity/2) // jezeli rozmiar funkcji jest o polowe mniejsza niz polowa rozmairu
            {
                capacity = capacity/2; 
                T* newlist = new T[capacity]; // tworzymy nowa liste ktora bedzie miala o polowe pomnijeszony rozmiar niz wczesniej 
                for(int i=0;i<size;i++)
                {
                    newlist[i] = array[i]; // ponone przypisanie elemetow starej listy no nowej listy
                }
                delete[] array; // usuniecie starej tablicy
                array = newlist; // przypisanie do zmiennej array nowej tablicy 
            } else {
                return;
            }
        }

        void swap(int index_1, int index_2)
        {
            T buffer = array[index_1];
            array[index_1] = array[index_2];
            array[index_2] = buffer;
        }

        /*void print_array() // funckja majaca na celu wydrukowanie calosci elementow oraz wyswietlisc rozmiar i pojemnosc tablicy
        {
            for(int i=0;i<size;i++)
            {
                std::cout << array[i] << " ";
            }
            std::cout << "Size is " << getSize() << std::endl << "Capasity is " << getCapasity() << std::endl;
        }*/

        void change_value_at_position(int location) // funckja majaca na celu zmiene wartosci w daenj konktretej lokalizacji
        {
            array[location] = 18;
        }
        

        ~DynamicArray() //dekonostruktor
        {
            delete[] array; // usuwa caly array z pamiecie
        }

};

