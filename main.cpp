#include "libraryDef.cpp"
#include "materialDef.cpp"
#include <ctime>
#include <iostream>

void signUp (library & lib) {
     std::string id;
     std::cout << "please enter your id: " << std::endl;
     std::cin >> id;
     lib.add_new_user(id);
}

int main() {
     library lib;
     borrower *user = nullptr;
     admin admin;
     std::string id{};
     unsigned int book_id = 0;
     std::string book_name{};
     char c = 0;
     std::string rights{};
     int count = 0;
     std::string password{};
     
     while (true) {
          std::cout << "Library Administration System. \n Please press E to enter your ID and password or press S to sign up." << std::endl;
          std::cin >> c;
     
          if (c == 'E'){
               std::cout << "Please enter your id below.\n";
               std::cin >> id;
               if (lib.user_exists(id)) {
                    //polymorphism
                    user = search_by_b_id(std::string id);
                    std::cout << "Welcome " + user->get_name() << std::endl;
                    if (id[0] == 'S') {
                         rights = "student";
                         break;
                    } else if (id[0] == 'T') {
                         rights = "staff";
                         break;
                    } else if (id == "Admin"){
                         while (true) {
                              std::cout << "Please enter admin password." << std::endl;
                              std::cin >> password;
                              if (password == "dhiusousou12123") {
                                   rights = "admin";
                                   break; 
                              } else if (count >= 4) {
                                   std::cout << "You have entered incorrect password too many times. For security reasons, the program will end.\n";
                                   return;
                              } else {
                                   std::cout << "Incorrect password, you have " + std::to_string(4-count) + "chances" << std::endl;
                                   ++count;
                              }

                         }
                    }
               } else {
                    std::cout << "ID not found, please press [M] to return to main menu or press [S] to sign up" << std::endl;
                    std::cin >> c;
                    if (c == 'S') {
                         signUp(lib);
                    } else if (c == 'M') {
                         break;
                    }
               }

          } else if (c == 'S') {
               signUp (lib);
          } else {
               std::cout << "Invalid input." << std::endl;
          }
          
     }

     if (rights == "student" || rights == "staff"){
          while (true) {
               std::cout << "Library Administration System.\nMenu: [S] Search [Q] Quit [P] Personal info" << std::endl;
               std::cin >> c;
               if (c == 'S') {
                    while (true){
                         std::cout << "[I] Search by id [N] Search by name" << std::endl;
                         std::cin >> c;
                         if (c == 'I'){
                              std::cout << "Please enter book id" << std::endl;
                              std::cin >> book_id;
                              materials *m = lib.search_by_id(book_id);
                              // print pointer content
                              // m.print();
                         }
                         else if (c == 'N')
                         {
                              std::cout << "Please enter book name" << std::endl;
                              std::cin >> book_name;
                              materials *m = lib.search_by_name(book_name);
                         }
                         else
                         {
                              std::cout << "Invalid input" << std::endl;
                         }
                    }
               } else if (c == 'Q') {
                    std::cout << "Hope you have a nice day and enjoy your books." << std::endl;
                    return;
               } else if (c == 'P') {
                    user->borrowed_list();
                    std::cout << "Return[R] Borrow[B]" << std::endl;
                    std::cin >> c;
                    std::cout << "Please enter the book's id" << std::endl;
                    std::cin >> book_id;
                    if (c == 'R') {
                         user->return_book(lib.search_by_id(book_id));
                         std::cout << (lib.search_by_id(book_id))->get_name() + "has been returned." << std::endl;
                    } else if (c = 'B') {
                         user->borrow_book(lib.search_by_id(book_id));
                         std::cout << (lib.search_by_id(book_id))->get_name() + "has been borrowed." << std::endl;
                    } else {
                         std::cout << "Invalid input." << std::endl;
                    }
               } else {
                    std::cout << "Invalid input.\nMenu: [S] Search [Q] Quit [P] Personal info" << std::endl;
               }
          }
     } else if (rights == "admin") {
          while (true) {
               std::cout << "Library Administration System.\nMenu: [S] Search [Q] Quit [E] Edit list state" << std::endl;
               std::cin >> c;
               if (c == 'S') {
                    while (true){
                         std::cout << "[I] Search by id [N] Search by name" << std::endl;
                         std::cin >> c;
                         if (c == 'I'){
                              std::cout << "Please enter book id" << std::endl;
                              std::cin >> book_id;
                              lib.search_by_id(book_id);
                              //print
                         } else if (c == 'N') {
                              std::cout << "Please enter book name" << std::endl;
                              std::cin >> book_name;
                              lib.search_by_name(book_name);
                         } else {
                              std::cout << "Invalid input" << std::endl;
                         }
                    }
               } else if (c == 'Q'){
                    std::cout << "Hope you have a nice day." << std::endl;
                    return;
               } else if (c == 'E'){
                    std::cout << "Return[R] Borrow[B]" << std::endl;
                    std::cin >> c;
                    std::cout << "Please enter the book's id" << std::endl;
                    std::cin >> book_id;
                    if (c == 'R') {
                         lib.set_state_list_return(lib.search_by_id(book_id));
                         std::cout << (lib.search_by_id(book_id))->get_name() + "has been returned." << std::endl;
                    } else if (c == 'B') {
                         lib.set_state_list_borrow(lib.search_by_id(book_id));
                         std::cout << (lib.search_by_id(book_id))->get_name() + "has been borrowed." << std::endl;
                    } else {
                         std::cout << "Invalid input." << std::endl;
                    }
               } else {
                    std::cout << "Invalid input.\nMenu: [S] Search [Q] Quit [E] Edit list state" << std::endl;
               }
          }
     }
     return 0;
}

