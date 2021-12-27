#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex> //include <string>
//#include <format>
#include <string>
//#include <format>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <functional>
#include <cmath>


std::map<std::string, std::string> g_pages;
std::map<const std::string*, const std::string*> g_imps;
std::map<const int*, const int*> g_ints;
std::map<int, int> g_not_pointers;
std::mutex g_pages_mutex;
std::mutex m;

//template <class P, class Z>
/*void print(Z key, P value) {
    std::cout << key << value << std::endl;
}*/

void doSthRvalue(int&& dols) {
    std::cout << "doSthRvalue: " << dols << std::endl;
}

//merge functions

void doSthLvalue(int& dols) {
    std::cout << "doSthLvalue: " << dols << std::endl;
}

void doSthDoubt(int& dols) {
    std::cout << "Doubt: " << dols << std::endl;
}

template <class... V>
void print(V&&... args) { // --> not V&... args
    //TODO: try a different thing?
    ((std::cout << std::forward<V>(args) << "\n"), ...);
}

struct Mult {
private:
    int fact;

public:
    Mult(int x) : fact(x) {}

    int operator()(int oths) {
        return fact * oths;
    }
};

struct Pow {
private:
    int x = 4;

public:
    Pow(int p) : x(p) {}
    Pow() : x(4) {}
    //Pow(int p) : x(p){}
    int operator()(int z) {
        std::cout << "transformed vect " << z << ": " << pow(z, x) << std::endl;
        return pow(z, x);
    }
};

struct Int { 
    int value;
    //friend modifier?
    //operator+()?

    int operator()(int z) {
        return z * 5;
    }

    /*friend int operator-(const int& x, const int& z) {
        return x * z;
    }
    
    int operator[](const int& x, const int& z) {
        return x * z;
    }

    friend int operator=(const int& x, const int& z) {
        return x * z;
    }

    friend int operator()(int z) {
        return z * 5;
    }*/

    /*friend int operator()(const int& x, const int& z) {
        return x * z;
    }*/
    
    /*friend int operator+(const int& x, const int& z) {
        return x + z;
    }*/
};

Int operator+(const Int& lhs, const Int& rhs)
{
    return Int{ lhs.value + rhs.value };
}

struct Bar {
    int num_;
    Bar(int num) : num_(num) {}
    void print_ad(int i) const {
        std::cout << "Num intended: " << num_ + i << std::endl;
    }

    void print_nc(int& i) {
        std::cout << "Num print_nc: " << num_ + i << std::endl;
    }

    void func_test(int& i) {
        std::cout << "Func test: " << num_ + i << std::endl;
    }
};

void notInBar(int& num) {
    std::cout << "notInBar: " << num + 693734 << std::endl;
}

void takeFromOutside_(std::vector<int>& vect, std::string& st, /*void(*fun)(int&, std::string)*/ const std::function<void(int&, std::string)>& fun) {
    for (auto& el : vect) {
        fun(el, st);
        //std::cout << "Taken from vector: " << el << ", int from outside: " << 
    } 
}

void take_ptr_(std::vector<int>& vect, std::string& i, void(*fun)(int&, std::string)) {
    for (auto& el : vect) {
        fun(el, i);
        
    } 
}

/*void take_lambda_pointerr_(std::vector<int>& vect, std::string& i, void(*fun)(int&, std::string)) {
    for (auto& el : vect) {
        fun(el, i);
        
    } 
}*/

void doSth(int& x, std::string a) {
    std::cout << "take_ptr_: " << x << ", " << a << std::endl;
}

//auto lambd = [](int& x, std::string a){ std::cout << "take_ptr_lambda_: " << x << ", " << a << std::endl; }; // --> not declarable as "void"

//TODO: study namespaces
//TODO: forward ref 
//TODO: std::reference_wrapper

void someRef_(int& x, std::vector<std::string>& vect, std::string(*func)(std::string&)) {
    for (auto& es : vect) {
        std::string st = (**func)(es); // --> does *func(es) work? --> it does not: // nor with &: src_nofmt.cpp:166:33: error: expression cannot be used as a function
                                                                            /*src_nofmt.cpp: In function 'void someRef_(int&, std::vector<std::__cxx11::basic_string<char> >&, std::string (*)(std::string&))':
                                                                            src_nofmt.cpp:166:26: error: no match for 'operator*' (operand type is 'std::string' {aka 'std::__cxx11::basic_string<char>'})
                                                                            166 |         std::string st = *func(es);
                                                                                |                          ^~~~~~~~~*/
        std::cout << "Vector element: " << es << ", equis: " << x << ", lambda mod:   " << st << std::endl; 
        std::cout << "func location: " << &func << std::endl;
    }
}

void somePtr_(int& x, std::vector<std::string>& vect) {
    for (auto& es : vect) {
        std::cout << "Vector element from somePtr_: " << es << ", equis: " << x << std::endl;
    }
}

const void somePtrConst_(int& x, std::vector<std::string>& vect) {
    for (auto& es : vect) {
        std::cout << "Vector element from somePtr_: " << es << ", equis: " << x << std::endl;
    }
}

void ptrVsRef_() {
    auto lambdaFun_ = [](std::string& p) -> std::string {
        p = p + " _modified by lambda";
        return p;
    };
    //void(&lambda_ref_)(std::string&) = lambdaFun_;

    const int& ref = 10;
    const int&& ref1 = 10;
    int&& rv_ref = 10;

    int f = 23;
    int& f_ref = f;
    int&& f_rva = 23;
    std::vector<std::string> myVetc_ = { "You", "Are", "A", "Freaking", "Fallero" };
    //cannot add more than one "*" to declare function pointer (ie "void(**somePtrPointed_)(int&, std::vector<std::string>&) = &somePtr_;")
    //cannot add more than one "&" to "&somePtr_", (ie "void(*somePtrPointed_)(int&, std::vector<std::string>&) = &&somePtr_;")
    //can only put 1 ampersand everywhere except from rvalue references and function references, where we can put up to 2 ampersands
    int& f_ref1 = f_ref;
    void(*somePtrPointedMinusOne_)(int&, std::vector<std::string>&) = somePtr_;
    void(*somePtrPointed0_)(int&, std::vector<std::string>&) = &somePtr_;
    void(**somePtrPointed1_)(int&, std::vector<std::string>&) = &somePtrPointed0_;
    void(***somePtrPointed2_)(int&, std::vector<std::string>&) = &somePtrPointed1_;
    void(****somePtrPointed3_)(int&, std::vector<std::string>&) = &somePtrPointed2_;
    void(&somePtrReferenced0_)(int&, std::vector<std::string>&) = *somePtrPointed0_; // --> FIRST, read below line. Here, as we are declaring a lvalue reference, "somePtrPointed0_" is always going to be dereferenced to a function pointer and NOT a raw function because there is only one "&" in "&somePtrReferenced0_". So if we want to make it a rvalue function reference, we will have to explicitely write two "&" here: "&somePtrReferenced0_", so it will look like this "&&somePtrReferenced0_", just like below.
    void(&&somePtrReferenced1_)(int&, std::vector<std::string>&) = *somePtrPointed0_; // --> as many "*" as you want; in this case, "somePtrReferenced0_" is a rvalue reference, and somePtrPointed0_ has to be dereferenced with at least one "*" because otherwise it is implicitly converted to a function pointer, as it is located at an rvalue context
    void(&&somePtrReferenced2_)(int&, std::vector<std::string>&) = **somePtrPointed1_;
    void(&&somePtrReferenced3_)(int&, std::vector<std::string>&) = ***somePtrPointed2_;
    void(&&somePtrReferenced4_)(int&, std::vector<std::string>&) = ****somePtrPointed3_;
    void(&somePtrReferenced5_)(int&, std::vector<std::string>&) = somePtr_;
    void(&&somePtrReferenced6_)(int&, std::vector<std::string>&) = somePtr_;
    void(&&somePtrReferenced7_)(int&, std::vector<std::string>&) = *somePtr_;

    void(&somePtrReferencedOnce1_)(int&, std::vector<std::string>&) = **somePtrPointed1_;
    void(&somePtrReferencedOnce2_)(int&, std::vector<std::string>&) = ***somePtrPointed2_;
    void(&somePtrReferencedOnce3_)(int&, std::vector<std::string>&) = ****somePtrPointed3_;

    const void(&somePtrConsted0_)(int&, std::vector<std::string>&) = somePtrConst_;

    //void recout = std::cout << "Out" << std::endl; --> NOT POSSIBLE

    //void(&someRealFunc_)() = std::reference_wrapper<void()> --> NOT POSSIBLE

    /*void(&&someRealFunc_)(int&, std::vector<std::string>&) = (int& z, std::vector<std::string>& p) {
       for (auto x : p) {
           std::cout << "Current x is: " << x << ", and z int selected is: " << z << std::endl;
       }
    };*/
    
    
    /*[](int& z, std::vector<std::string>& p) {
       for (auto x : p) {
           std::cout << "Current x is: " << x << ", and z int selected is: " << z << std::endl;
       }
    };*/

    
    //(&&somePtr_)(f, myVetc_); --> NOT POSSIBLE

    //function pointers and raw functions are always converted to function pointers in rvalue context
    
    (****somePtr_)(f, myVetc_);
    somePtrPointed0_(f, myVetc_);
    (*somePtrPointed1_)(f, myVetc_);
    (**somePtrPointed2_)(f, myVetc_);
    (***somePtrPointed3_)(f, myVetc_);
    somePtrReferenced4_(f, myVetc_);
    (**************somePtrReferenced4_)(f, myVetc_);
    
    someRef_(f_ref, myVetc_, lambdaFun_);
    
    //someRef_(f_ref, myVetc_, lambda_ref_);
}


//template <typename X> --> if written, it has to be used compulsorily
void transform() {
    int vect[5] = { 1, 3, 5, 7, 9 };
    for (int i = 0; i < 5; ++i) {
        std::cout << "UnTransformed vect " << i << ": " << vect[i] << std::endl;
    }
    int ok = 5;
    int& amper = ok;
    int* ptrs0 = &ok;
    int** ptrs1 = &ptrs0;
    int*** ptrs2 = &ptrs1;

    //int thed = Int(5);
    //auto result = std::async(Int.operator+, Int{ 1 }, 2);

    Bar origBar(8743);

    ////void(*fncPointer_)(int&, std::string);

    int s = 33; 

    auto fncPointer_ = [=](int& x, std::string a) mutable { s = 2; std::cout << "fncPointer_: " << x << ", " << a << std::endl; std::cout << "external rvalue reference: " << s << std::endl; };

    std::function<void(const Bar&, int)> f_add = &Bar::print_ad;
    std::function<void(Bar const&, int)> f_add_m = &Bar::print_ad;
    std::function<void(Bar const&, int)> f_add_r = &Bar::print_ad;
    std::function<void(Bar, int&)> f_add_nc = &Bar::print_nc; //cant go without ampersand, but Bar& can go without it (at least in mac with g++)
    std::function<void(Bar&, int&)> func_test = &Bar::func_test;
    std::function<void(int)> out_Bar_lambda = [&](int x) {
        std::cout << "Out bar lambda: " << std::endl;
        notInBar(amper);
    };
    const Bar bar(5437);
    Bar bar1(7438);
    f_add(bar, 2);
    f_add(5437, 2);
    f_add_r(bar, 4);
    f_add_r(5437, 4);
    out_Bar_lambda(8349);
    int pure = 64;
    int& ref = pure;
    f_add_nc(bar1, ref);

    std::vector<int> theVect = { 1, 2, 3, 4, 5, 6 };
    std::string trial = "takenFromOutside";
    std::string dt = "doSth";
    std::string lam = "lambdessa";
    std::string& lsd = lam;
    std::string lamer = "myFunlambda_ptrs_";

    auto lambd = [](int& x, std::string a){ std::cout << "take_ptr_lambda_: " << x << ", " << a << std::endl; }; // --> not declarable as "void"
    typedef void(*Lambda_ptr_)(int&, std::string);

    //note: can only pass lambda as a function pointer only in case it doesnt capture anything
    Lambda_ptr_ myFun {
        [](int& x, std::string a){
            std::cout << "Lambda_ptr_ my funs: " << x << ", " << a << std::endl;
        }
    };

    takeFromOutside_(theVect, trial, fncPointer_);
    take_ptr_(theVect, dt, &doSth);
    take_ptr_(theVect, lsd, lambd);
    take_ptr_(theVect, lamer, myFun);

    auto result = std::async(operator+, Int{ 1 }, Int{ 1 });
    auto result2 = std::async(std::launch::async, Int(), 2);
    std::cout << "from async0 I get " << result.get().value << "\n";
    std::cout << "from async1 I get " << result2.get() << "\n";
    std::transform(vect, vect + 5, vect, Pow(2));
    //auto futur = std::async(std::launch::async, Pow(), 2);
    for (int i = 0; i < 5; ++i) {
        std::cout << "transformed vect " << i << ": " << vect[i] << std::endl;
    }

    ptrVsRef_();

}


struct X {
    void foo(int i, const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
    void bar(const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }

    int operator ()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        int total = i + 10;
        
        return total;
        ////return &total;
        
    }

//private:
    /*int *operator ()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        int total = i + 10;
        int* ptr = &total;
        return ptr;
        ////return &total;
        //return (i + 10);
        //std::cout << "I + 10: " << i + 10 << std::endl;
    }*/
};


template <typename RandomIt> //or "<class RandomIt>"
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);

    RandomIt mid = beg + len / 2;
    auto handle = std::async(std::launch::async,
        parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}

void async() {
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
    
    X x;
    // Calls (&x)->foo(42, "Hello") with default policy:
    // may print "Hello 42" concurrently or defer execution
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // Calls x.bar("world!") with deferred policy
    // prints "world!" when a2.get() or a2.wait() is called
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // Calls X()(43); with async policy
    // prints "43" concurrently
    auto a3 = std::async(std::launch::async, X(), 43);
    auto a4 = std::async(std::launch::async, x, 93); // --> if we add & before x, it has to be only for a function defined in x struct, not for an operator () in this case
    a2.wait();                     // prints "world!"
    //int result = *a3.get();
    int yes = 22;
    int& refr = yes;
    int& refr2 = refr;
    int& refr3 = refr2;
    //int&& refr4 = yes; or int&& refr4 = refr3 --> not possible
    refr = 23;
    int* pntr = &yes;
    int nots = yes;
    nots = 24;
    //lvalue reference
    /*int s = 5;
    int& lvalue = s;*/

    //rvalue reference
    int&& rvalue = 2;

    //rvalue vs lvalue references example
    doSthRvalue(3);
    int preLval = 4;
    int& lvalue = preLval;
    doSthLvalue(lvalue);
    int sth = 5;
    doSthDoubt(sth);

    print("Nots: ", nots);
    print("Yes: ", yes);
    print("Refr (technically has to be equal to yes): ", refr);
    print("Refr2 (technically has to be equal to yes): ", refr2);
    print("Refr3 (technically has to be equal to yes): ", refr3);
    

    //print("Refr: ", refr);
    print("\n");
    //free(pntr);
    //print("HexdecValue: ", std::format("{:#x}", refr));
    print("\n");
    //free(pntr);
    print("Pointer: ", pntr);
    //free(pntr);

    int* bits = (int*)calloc(4, sizeof(int));
    for (int i = 0; i < 4; ++i) {
        bits[i] = i+1;
    }
    
    
    //std::string formatted_bits = std::format("{:#x}", bits);
    //std::cout << "UnFormatted_bits: " << bits << std::endl;
    ////int clse = &yes; --> not possible
    //std::cout << result << '\n'; // prints "53"
    std::cout << "a3.get: " << a3.get() << '\n'; //prints the num 53
    std::cout << "a4.get: " << a4.get() << '\n'; //prints the num 53
    //std::cout << a3.get() << '\n'; // prints memory address
    std::cout << "UnFormatted_bits: " << bits << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Current bits i: " << bits[i] << std::endl;
        std::cout << "Current bits i location: " << &bits[i] << std::endl;
    }
    
    transform();

    //free(pntr);
    std::cin.get();
    free(bits);
    //free(pntr);
    //std::cout << "numero: " << std::format("{:#x}", result) << std::endl;
}

template <class T>
void bubbleSort(T a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; i < j; j--)
            if (a[j] < a[j - 1])
                std::swap(a[j], a[j - 1]);
}


template <typename T>
T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

void save_page(const std::string& url, const int& psd, int dog, int num)
{
    // simulate a long page fetch


    std::this_thread::sleep_for(std::chrono::milliseconds(0));
    std::string result = "fake content";

    const std::string* ptr = &url;
    const int* psa = &psd;

    std::cout << "No mutex " << num << "... " << std::endl;
    //std::cout << "Drugs... " << std::endl;
    g_pages_mutex.lock();
    std::cout << "Drugs " << num << "... " << std::endl;
    std::cout << "Threading " << num << "... " << std::endl;
    g_imps[ptr] = ptr;
    g_ints[psa] = psa;
    g_pages[url] = result;
    g_not_pointers[dog] = dog;
 
    g_pages_mutex.unlock();
    //std::cout << "No mutex after " << num << std::endl;
    //std::cout << "No mutex after " << num << "... " << std::endl;
    //or std::lock_guard<std::mutex> guard(g_pages_mutex);
}

int main()
{
    std::thread t1(save_page, "http://foo", 8, 94324, 1);
    //std::cout << "join test" << std::endl;
    std::thread t2(save_page, "http://bar", 8, 432994234, 2);
    int inter = 94390;
    
    t1.join();
    //std::cout << "join test" << std::endl; --> if put here it can sometimes cout between both "Threading... "s.
    //std::thread t2(save_page, "http://bar", 8, 432994234, 2);
    //t2.join();
    g_pages_mutex.lock();
    std::cout << "join test" << std::endl;
    g_pages_mutex.unlock();
    //t1.detach();
    t2.join();
    //std::cout << "join test" << std::endl;
    //t2.detach();

    //std::cout << "my int: " << std::format("{:#x}", inter) << std::endl;
    int* ptrs = &inter;
    std::cout << "Ptrs: " << ptrs << std::endl;
    
   
    
    for (const auto& pair : g_not_pointers) {
        //std::cout << "g_not_pointers 1: " << std::format("{:#x}", pair.first) << std::endl << "g_not_pointers 2: " << std::format("{:#x}", pair.second) << std::endl;
        std::cout << "locations: " << &pair.first << " => " << &pair.second << '\n';
        std::cout << pair.first << " => " << pair.second << '\n';
    }

    for (const auto& pair : g_pages) {
       //td::cout << "pages: " << std::format("{:x}", pair.first) << std::format("{:x}", pair.second) << std::endl;
        std::cout << pair.first << " => " << pair.second << '\n';
    }
    for (const auto& pair : g_imps) {
        //std::cout << "imps: " << std::format("{:x}", pair.first) << std::format("{:x}", pair.second) << std::endl;
        std::cout << pair.first << " => " << pair.second << '\n';
    }
    for (const auto& pair : g_ints) {
        //std::cout << "ints: " << std::format("{:x}", pair.first) << std::format("{:x}", pair.second) << std::endl;
        std::cout << pair.first << " => " << pair.second << '\n';
    }

    std::cout << myMax<int>(3, 7) << std::endl;  // Call myMax for int
    std::cout << myMax<double>(3.0, 7.0) << std::endl; // call myMax for double
    std::cout << myMax<char>('g', 'e') << std::endl;   // call myMax for char

    int a[5] = { 10, 50, 30, 40, 20 };
    int n = sizeof(a) / sizeof(a[0]);

    std::cout << "\nSize of a: " << sizeof(a) << std::endl;
    std::cout << "Size of a[0]: " << sizeof(a[0]) << std::endl;
    std::cout << "n: " << n << std::endl;

    // calls template function
    bubbleSort<int>(a, n);

    std::cout << "\nSorted array : ";
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    //t2.join();
    std::cin.get();

    async();

    std::cin.get();

    return 0;
}
