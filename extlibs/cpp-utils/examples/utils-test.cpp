#include <iostream>
#include <vector>

#include <utils/log.hpp>


void test_logs()
{
    std::cout<<"=== test_logs ==="<<std::endl;
    {
        using namespace utils::log::format;
        std::cout<<bold<<"bold"<<reset_bold<<"reset_bold"<<std::endl;
        std::cout<<dim<<"dim"<<reset_dim<<"reset_dim"<<std::endl;
        std::cout<<underline<<"underline"<<reset_underline<<"reset_underline"<<std::endl;
        std::cout<<blink<<"blink"<<reset_blink<<"reset_blink"<<std::endl;
        std::cout<<reverse<<"reverse"<<reset_reverse<<"reset_reverse"<<std::endl;
        std::cout<<hidden<<"hidden"<<reset_hidden<<"reset_hidden"<<std::endl;
        std::cout<<strikeout<<"strikeout"<<reset_strikeout<<"reset_strikeout"<<std::endl;
    }

    
    {
        using namespace utils::log::colors;
        std::cout<<black<<"black"<<std::endl;
        std::cout<<red<<"red"<<std::endl;
        std::cout<<green<<"green"<<std::endl;
        std::cout<<yellow<<"yellow"<<std::endl;
        std::cout<<blue<<"blue"<<std::endl;
        std::cout<<magenta<<"magenta"<<std::endl;
        std::cout<<cyan<<"cyan"<<std::endl;
        std::cout<<light_gray<<"light_gray"<<std::endl;
        std::cout<<dark_gray<<"dark_gray"<<std::endl;
        std::cout<<light_red<<"light_red"<<std::endl;
        std::cout<<light_green<<"light_green"<<std::endl;
        std::cout<<light_yellow<<"light_yellow"<<std::endl;
        std::cout<<light_blue<<"light_blue"<<std::endl;
        std::cout<<light_magenta<<"light_magenta"<<std::endl;
        std::cout<<light_cyan<<"light_cyan"<<std::endl;
        std::cout<<white<<"white"<<std::endl;
        std::cout<<reset<<"reset"<<std::endl;
    }

    {
        using namespace utils::log::bg;
        std::cout<<black<<"black"<<std::endl;
        std::cout<<red<<"red"<<std::endl;
        std::cout<<green<<"green"<<std::endl;
        std::cout<<yellow<<"yellow"<<std::endl;
        std::cout<<blue<<"blue"<<std::endl;
        std::cout<<magenta<<"magenta"<<std::endl;
        std::cout<<cyan<<"cyan"<<std::endl;
        std::cout<<light_gray<<"light_gray"<<std::endl;
        std::cout<<dark_gray<<"dark_gray"<<std::endl;
        std::cout<<light_red<<"light_red"<<std::endl;
        std::cout<<light_green<<"light_green"<<std::endl;
        std::cout<<light_yellow<<"light_yellow"<<std::endl;
        std::cout<<light_blue<<"light_blue"<<std::endl;
        std::cout<<light_magenta<<"light_magenta"<<std::endl;
        std::cout<<light_cyan<<light_cyan<<std::endl;
        std::cout<<white<<"white"<<std::endl;
        std::cout<<reset<<"reset"<<std::endl;
    }

    {
        using namespace utils::log;
        todo("information test");
        todo("test_logs","information","test");

        info("information test");
        info("test_logs","information","test");

        warning("information test");
        warning("test_logs","information test");

        error("information test");
        error("test_logs","information test");

        critical("information test");
        critical("test_logs","information test");

        log(LOG_LVL::TODO,"information test");
        log(LOG_LVL::TODO,"test_logs","information test");

        log(LOG_LVL::INFO,"information test");
        log(LOG_LVL::INFO,"test_logs","information test");

        log(LOG_LVL::WARN,"information test");
        log(LOG_LVL::WARN,"test_logs","information test");

        log(LOG_LVL::ERR,"information test");
        log(LOG_LVL::ERR,"test_logs","information test");

        log(LOG_LVL::CRIT,"information test");
        log(LOG_LVL::CRIT,"test_logs","information test");
    }
    std::cout<<"=== END test_logs ==="<<std::endl;
}

#include <utils/maths.hpp>
void test_maths()
{
    std::cout<<"=== test_maths ==="<<std::endl;

    using namespace utils::maths;
    std::cout<<"sign(-42)"<<sign(-42)<<std::endl;
    std::cout<<"sign(42)"<<sign(42)<<std::endl;
    std::cout<<"sign(0)"<<sign(0)<<std::endl;
    std::cout<<"sign(-42.8)"<<sign(-42.8)<<std::endl;
    std::cout<<"sign(42.8)"<<sign(42.8)<<std::endl;
    std::cout<<"sign(0.f)"<<sign(0.f)<<std::endl;

    std::cout<<"min(1,2)"<<min(1,2)<<std::endl;
    std::cout<<"min(-1,-2)"<<min(-1,-2)<<std::endl;
    std::cout<<"min(0,1)"<<min(0,1)<<std::endl;
    std::cout<<"min(-1,0)"<<min(-1,0)<<std::endl;
    std::cout<<"min(0,0)"<<min(0,0)<<std::endl;
    std::cout<<"min(1,2,2,3,4,5)"<<min(1,2,3,4,5)<<std::endl;
    std::cout<<"min(1,2,-12,4,5)"<<min(1,2,-12,4,5)<<std::endl;
    std::cout<<"min(1,2,3,4,-5)"<<min(1,2,-12,4,5)<<std::endl;

    std::cout<<"max(1,2)"<<max(1,2)<<std::endl;
    std::cout<<"max(-1,-2)"<<max(-1,-2)<<std::endl;
    std::cout<<"max(0,1)"<<max(0,1)<<std::endl;
    std::cout<<"max(-1,0)"<<max(-1,0)<<std::endl;
    std::cout<<"max(0,0)"<<max(0,0)<<std::endl;
    std::cout<<"max(1,2,2,3,4,5)"<<max(1,2,3,4,5)<<std::endl;
    std::cout<<"max(1,2,12,4,5)"<<max(1,2,-12,4,5)<<std::endl;
    std::cout<<"max(1,2,3,4,12)"<<max(1,2,-12,4,5)<<std::endl;

    std::cout<<"5^5= "<<utils::maths::power<5>::of(5)<<std::endl;


    std::vector<int> v;
    for(int i=0;i<100;++i)
        v.push_back(i);

    int size = v.size();

    std::vector<int> v2 = discretize(v,[size](double a)->double{
         return 1.0/ker::gaussian(a,0.55);
    });

    std::cout<<"Discretisation avec 1/gauss(a,0.55,0) sur un vecteur de [0 ..99] : Size = "<<v2.size()<<" contenu:"<<std::endl;
    for(int i : v2)
        std::cout<<i<<" ";
    std::cout<<"\n fin discretisation"<<std::endl;

    std::cout<<"=== END test_logs ==="<<std::endl;
}

#include <utils/string.hpp>
void test_string()
{
    std::cout<<"=== test_string ==="<<std::endl;

    using namespace utils::string;
    std::string base = "test testtest testestestestest";
    std::cout<<"Base:"<<base<<std::endl;

    std::cout<<"split(base,\" \")"<<std::endl;
    for(auto& s : split(base," "))
        std::cout<<s<<std::endl;

    std::cout<<"replace(base,\"test\",\"blah\")"<<std::endl;
    replace(base,"test","blah");
    std::cout<<"Base:"<<base<<std::endl;

    std::cout<<"join(\"/\",split(base,\"bl\"))"<<std::endl;
    std::cout<<join("|",split(base,"bl"))<<std::endl;

    std::cout<<join("|",1,2,3,"blaghjio",42.f)<<std::endl;

    std::cout<<"startswith(\"test\",\"te\") "<<startswith("test","te")<<std::endl;
    std::cout<<"startswith(\"test\",\"es\") "<<startswith("test","es")<<std::endl;

    std::cout<<"endswith(\"test\",\"st\") "<<endswith("test","st")<<std::endl;
    std::cout<<"endswith(\"test\",\"et\") "<<endswith("test","et")<<std::endl;

    std::cout<<"=== END test_logs ==="<<std::endl;
}

#include <utils/sys.hpp>
void test_sys()
{
    std::cout<<"=== test_sys ==="<<std::endl;
    {
        using namespace utils::sys;
        std::cout<<"whereis: "<<whereis("g++")<<std::endl;

        Compiler comp;
        Library libf = comp.input("f.cpp")
            .output("f")
            .flags("-o3","-Wall")
            .get();

        if(libf.load())
        {
            if(libf.load_f<int,int>("print"))
                libf["print"]->call<int>(21);
            //cast test
            int(*cast)(int) =  *reinterpret_cast<utils::func::Func<int,int>*>(libf["print"]);
            cast(22);
            
            libf.close();
        }
    }

    {
        using namespace utils::sys::dir;
        std::cout<<"dir::create: "<<create("/tmp/test")<<std::endl;
        std::cout<<"dir::rm: "<<rm("/tmp/test",true)<<std::endl;

        std::cout<<"dir::create: "<<create("/tmp/test")<<std::endl;
        std::cout<<"dir::rm_if_empty: "<<rm_if_empty("/tmp/test",true)<<std::endl;
    }

    {
        using namespace utils::sys::file;

        std::cout<<"file::touch: "<<touch("/tmp/test/file")<<std::endl;
        std::cout<<"file::exist: "<<exists("/tmp/test/file")<<std::endl;
        std::cout<<"file::rm: "<<rm("/tmp/test/file")<<std::endl;
    }
    std::cout<<"=== END test_logs ==="<<std::endl;
}


#include <utils/thread.hpp>
void test_thread()
{
    std::cout<<"=== test_thread ==="<<std::endl;
    utils::thread::Pool pool(5);
    pool.push(test_logs);
    pool.push(test_maths);
    pool.push(test_string);
    pool.push(test_sys);
    pool.push(test_logs);
    pool.push(test_maths);
    std::cout<<"=== END test_thread ==="<<std::endl;

    pool.wait();
}

#include <utils/functional.hpp>
double f(int a,int b)
{
    std::cout<<"double f("<<a<<" "<<b<<")"<<std::endl;
    return 41.5;
}

void f2(int a,int b)
{
    std::cout<<"void f2("<<a<<" "<<b<<")"<<std::endl;
}

void test_functional()
{
    using namespace utils::func;
    std::cout<<"=== test functional ==="<<std::endl;

    std::cout<<"apply(f,std::make_tuple(1,5)) = "<<apply(f,std::make_tuple(1,5))<<std::endl;

    auto func=make_func(f);
    std::cout<<func(3,5)<<std::endl; //know complet type

    VFunc& vfunc=func;
    vfunc.call<double>(1,5); //must specify the return type

    auto func2=make_func(f2);
    func2(3,5); //know complet type

    VFunc& vfunc2=func2;
    vfunc2.call<void>(1,5); //must specify the return type

    std::cout<<"=== END test functional ==="<<std::endl;
}

#include <utils/plot.hpp>
void test_plot()
{
    using namespace utils::plot;
    Gnuplot g;

    g.cmd("plot cos(x)");

    std::cout<<"press a key to continue"<<std::endl;
    std::cin.get();
    g.clear();
    g.mod(Gnuplot::Mod::WINDOW);

    {
        auto x = {1,2,3,4};
        auto y = {1,4,2,5};

        g.add("test1");
        g[0].style(Serie::Style::points);
        g[0].addPoints(x,y);
        g[0].add("serie2");
        g[0][1].style(Serie::Style::lines);
        g[0][1].addPoints(x,y);
        g[0][1].addPoint(5,9);

        g.add("test2");
        g[1].style(Serie::Style::points);
        g[1].addPoints(x,y);
        g.draw();

        std::cout<<"press a key to continue"<<std::endl;
        std::cin.get();
        g.mod(Gnuplot::Mod::MULTI);
        g.draw();

        std::cout<<"press a key to continue"<<std::endl;
        std::cin.get();
        g.mod(Gnuplot::Mod::HYBRID);
        g.draw();

    }

    std::cout<<"press a key to close"<<std::endl;
    std::cin.get();
    g.close();
}

#include <utils/memory.hpp>
void test_memory()
{
    using namespace utils::memory;
    std::cout<<"========== memory ======="<<std::endl;

    Pool<double> pool;
    pool.resize(42);
    pool.emplace(0,12);
    pool.emplace(4,15);
    pool.emplace(1,12);

    for(auto it = pool.begin(); it != pool.end();++it)
        std::cout<<it.index()<<"=>"<<it.data()<<", ";
    std::cout<<std::endl;

    std::cout<<"erase index 1"<<std::endl;

    pool.erase(1);
    for(auto it = pool.begin(); it != pool.end();++it)
        std::cout<<it.index()<<"=>"<<it.data()<<", ";

    std::cout<<std::endl;
}

int main(int argc,char* argv[])
{
    test_logs();
    test_maths();
    test_string();
    test_sys();
    test_functional();
    test_plot();
    test_memory();

    //test_thread();


    return 0;
}
