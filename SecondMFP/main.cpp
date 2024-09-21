
/*Варіант 10: Генератор числових послідовностей.

1. Створити бібліотеку класів:

Реалізувати клас для генерації числових послідовностей (NumberSequenceGenerator).

Забезпечити можливість генерації арифметичних та геометричних послідовностей, визначення простих чисел тощо.

2. Реалізувати клієнтський додаток:

Використовуючи бібліотеку, створити клієнтський додаток для генерації числових послідовностей.

Додаток має демонструвати генерацію різних видів числових послідовностей та їх вивід.

3. Тестування програми:

Створити main() або клієнтську програму для тестування.

Провести тестування розробленої та реалізованої програми з використанням мультифайлової організації коду та ООП-підходу.*/
#include"NumberSequenceGenerator.h"
#include"UserInteraction.h"
int main() {
    UserInteraction ui;
    NumberSequenceGenerator seq;
    

    std::vector<std::string> operations{
        " <>Generate Arithmetic Progression",
        " <>Generate Geometric Progression",
        " <>Count prime numbers ",
        " <>Count even numbers",
        " <>Count odd numbers",
        " <>Display",
        " <>Exit"
     };
     int selectedOperationIndex = 0;

     while (true) {
         system("cls");
         std::cout << std::setw(55) << std::right << "--<<==" << "Sequence Generator" << "==>>--" << std::endl;
         std::cout << "  <<==Menu==>> " << std::endl;
         std::cout << "Choose operation: " << std::endl;
         for (int i = 0; i < operations.size(); ++i) {
             if (i == selectedOperationIndex) {
                 std::cout << "<-> " << operations[i] << std::endl;
             }
             else {
                 std::cout << "   " << operations[i] << std::endl;
             }
         }
         char keyPressed = _getch();
         switch (keyPressed) {
         case 72:
             selectedOperationIndex = (selectedOperationIndex - 1 + operations.size()) % operations.size();
             break;
         case 80:
             selectedOperationIndex = (selectedOperationIndex + 1) % operations.size();
             break;
         case 13: {
             switch (selectedOperationIndex) {
             case 0: {

                  seq.GenerateArithmeticProgression(ui.getFirstTerm(), ui.getSecondParameterD(), ui.getN());
                  ui.showMessage("Arithmetic Progression has been created successfully");

             } break;
             case 1: {
                 seq.GenerateGeometricProgression(ui.getFirstTerm(), ui.getSecondParameterR(), ui.getN());
                 ui.showMessage("Geometric Progression  has been created successfully");

             } break;

             case 2: {

                 int n = seq.countPrimaryNumbers();
                 if (n > 1) {
                     std::cout << "There are: " << n << " primary numbers";
                 }
                 else if (n == 1)
                 {
                     std::cout << "There is " << n << " primary number";
                 }
                 else {
                     std::cout << "There are no primary numbers";
                 }
             }
               break;

             case 3: {
                 int n = seq.countEvenNumbers();
                 if (n > 1) {
                     std::cout << "There are: " << n << " even numbers";
                 }
                 else if( n==1)
                 {
                     std::cout << "There is " << n << " even number";
                 }
                 else {
                     ui.showMessage("There are no even numbers");
                 }
             } break;
             case 4: {
                 int n = seq.countOddNumbers();
                 if (n > 1) {
                     std::cout << "There are: " << n << " odd numbers";
                 }
                 else if (n == 1)
                 {
                     std::cout << "There is " << n << " odd number";
                 }
                 else {
                     ui.showMessage("There are no odd numbers");
                 }
             } break;
             case 5: {
                 seq.display();
             } break;
             case 6: {
                 std::cout << "Exiting program..." << std::endl;
                 return 0;
             } break;
             default:
                 std::cout << "Invalid operation selected!" << std::endl;
                 break;
             }
             std::cout << "\n\nPress Enter to continue...";
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cin.get();
             system("cls");
         } break;
         default:
             break;
         }
     }


     return 0;

}