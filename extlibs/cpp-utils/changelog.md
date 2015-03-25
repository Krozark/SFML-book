0.1.8
=====

add memory namespace

memory
------

* add Pool<T> class that manage a memory pool of posible empty cells


0.1.7
=====

add plot namespace

sys
---

* add Library::get_f(const std::string& name)const

string
------

* add startswith(string,string)
* add endswith(string,string)

plot
----

* add Gnuplot class


functional
----------

* add call of void functions


0.1.6
=====

sys
---

* add bool file::exists(const std::string& file_path)
* add bool file::touch(const std::string& file_path)
* add std::string whereis(const std::string& finename)
* add Library
* add Compiler


0.1.5
=====

* Add namespace func for function management
* Add namespace tr for tests, ideas ...

Func
----

* apply(f, Args&& ... args) the c++14 apply function
* VFunc a base class of all function? This class is virtual
** .call<Ret>(Args&& ... args) call the function with the params args, and the return type Ret
* Func<Ret,Args...> a specilize class for VFunc
** Ret operator()(Args&& .. args) call the function as a function
* make_fuction(f) return a Function object

tr
--

Do not use function insid this namespace, there wille be moved in other namespace in the future

0.1.4
=====

Maths
----

Add power<N>::of(number) that compute the power at compile time
add ker namespace

* Add kernel functions for learning machin in utils::ker namespace
* add template<typename T> T discretize(const T& tab,std::function<double(double)> f);
* add template<typename T,typename Iterator> T discretize(Iterator first,Iterator last,std::function<double(double)> f);

Log
---

* add log::ok(args...) that print log in green

