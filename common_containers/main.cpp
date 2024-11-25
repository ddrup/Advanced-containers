#include <bits/stdc++.h>

#include "seq_container/vector/vector.h"

class S {
  S() = delete;
  S operator+(int x) {
    this->a += x;
    this->b += x;
    return (*this);
  }
  int a;
  double b;
};

// void print(auto rem, const s21::Vector<int>& c)
// {
//     std::cout << c.capacity() << " ";
//     std::cout << rem;
//     for (size_t i = 0;i < c.size(); ++i) {
//       std::cout << c[i] << ' ';
//     }
//     std::cout << '\n';
// }

int main() {
  //   s21::Vector<int> c = {1, 2, 3};
  //   print("The vector holds: ", c);

  //   c.resize(5);
  //   print("After resize up to 5: ", c);

  //   c.resize(2);
  //   print("After resize down to 2: ", c);

  //   c.resize(6, 4);
  //   print("After resize up to 6 (initializer = 4): ", c);

  //   std::cout << "\n\n\n";

  //   s21::Vector<std::string> letters;

  //   letters.push_back("abc");
  //   std::cout << "Size vector = " << letters.size() << " Capacity vector = "
  //   << letters.capacity() << "\n"; std::string s{"def"}; std::string
  //   s1{"def1"}; letters.push_back(std::move(s)); std::cout << "Size vector =
  //   " << letters.size() << " Capacity vector = " << letters.capacity() <<
  //   "\n"; letters.push_back(s1); std::cout << "Size vector = " <<
  //   letters.size() << " Capacity vector = " << letters.capacity() << "\n";

  //   std::cout << "std::vector letters holds: ";
  //   for (size_t i = 0;i < letters.size(); ++i)
  //       std::cout << std::quoted(letters[i]) << ' ';

  //   std::cout << "\nMoved-from string s holds: " << std::quoted(s) << '\n';

  //   std::cout << "\n\n\n";

  //   struct A{
  //     int a;
  //     double b;
  //   };

  //   s21::Vector<A> a(1,{1,1.0});
  //   a.emplace_back(5,3.3);
  //   for(size_t i = 0;i < a.size();++i){
  //     std::cout << a[i].a << " " << a[i].b << "\n";
  //   }

  // std::cout << "\n\n\n";

  // std::vector<int> b{1,2,3,4,5};
  // std::vector<int> b1{6,7,8,9,0};
  // auto it = b.begin();
  // auto it1 = b1.begin();
  // std::cout << *it << " " << *it1 << "\n";
  // b.swap(b1);
  // std::cout << *it << " " << *it1 << "\n";

  // int a1[10] = {1,2,3,4,5};
  // std::vector<int> v1;

  // std::copy_if(a1, a1+10,
  //   std::back_insert_iterator<std::vector<int>>(v1), [](int x) { return x % 2
  //   == 0; });

  // for(auto val : v1){
  //   std::cout << val << " ";
  // }

  // std::cout << "\n\n\n";

  // s21::Vector<int>::const_iterator iter = c.cbegin();
  // s21::Vector<int>::iterator iter1 = c.begin();
  // std::cout << *iter << "\n";

  //   iter = iter1; // convert iterator -> const iterator

  //   std::cout << "\n\n\n";

  // s21::Vector<std::string> vec{"abc", "xyz"};
  // s21::Vector<std::string> res{"xxx", "abc", "uuu", "xyz", "lll"};

  // std::string s1 = "xxx";
  // std::string s2 = "uuu";
  // std::string s3 = "lll";

  // vec.insert(vec.begin(), std::move(s1));
  // vec.insert(vec.begin() + 1,std::move(s2));
  // vec.insert(vec.end(), std::move(s3));

  // std::cout << std::endl;
  // vect.insert(vect.begin() + 2,5, 66);
  // std::for_each(vect.begin(),vect.end(), [](int x) { std::cout << x << "
  // ";});

  // std::cout << std::endl;
  // vect.insert(vect.begin(),2, 100);
  // std::for_each(vect.begin(),vect.end(), [](int x) { std::cout << x << " ";});

  // std::cout << std::endl;
  // vect.insert(vect.end(),2, 200);
  // std::for_each(vect.begin(),vect.end(), [](int x) { std::cout << x << "
  // ";});
  s21::Vector<int> vec{1, 2, 3, 4};
  s21::Vector<int> res{2};

  s21::Vector<int>::iterator it = vec.erase(vec.begin());

  it = vec.erase(vec.begin() + 1);

  it = vec.erase(std::prev(vec.end()));
}
