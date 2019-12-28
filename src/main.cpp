#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <array>
#include <FFT.hpp>
#include <iterator>
#include <algorithm>
#include <cctype>
// #include <fftw3.h>

using cmplx = std::complex<double>;
using csignal = std::vector<cmplx>;

auto real_val([](cmplx c){ return c.real(); });

double strtodb (const std::string& str)
{
    std::string str2 = str;
    double num;
    // str2.erase(str2.end());
    
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == '-'){ str2 += str[i]; }
        else if (str[i] == '.'){ str2 += str[i]; }
        else if (std::isdigit(str[i])) { str2 += str[i]; }
        else if (str[i] == 'n'){ str2 = '0'; }
        else if (str[i] == ',')
        {
            if (str2 != "")
            {
                std::stringstream stream(str2);
                stream >> num;
            }   
        }
    }
    return num;
}

int main()
{
    static constexpr size_t electrod_cnt = 8;
    static constexpr size_t used_electrod_cnt = 1; // electrod_cnt;

    const size_t leng{100};

    std::string fname = "debug.txt";
    // std::cout << "file to be transformed:\n";
    // std::cin >> fname;
    std::ifstream inFile;
    inFile.open(fname);

    if (!inFile)
    {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }


    std::string row;
    std::array<std::string, electrod_cnt> str_elcs;
    std::string str_acc1, str_acc2, str_acc3, str_tst;
    std::array<std::vector<double>, electrod_cnt> electrods;
    std::string date;

    std::ofstream odata;
    std::ofstream otrafo;

    odata.open("indata.dat");
    otrafo.open("FourierTransformed.dat");

    int n = 0;

    while (inFile >> row >> str_elcs[0] >> str_elcs[1] >> str_elcs[2] >> str_elcs[3] >> str_elcs[4] >> str_elcs[5] >> str_elcs[6] >> str_elcs[7] >> str_acc1 >> str_acc2 >> str_acc3 >> date >> str_tst)
    {
        if (odata.is_open())
        {
            std::string line = row + ' ' + str_elcs[0] + ' ' + str_elcs[1] + ' ' + str_elcs[2] + ' ' + str_elcs[3] + ' ' + str_elcs[4] + ' ' + str_elcs[5] + ' ' + str_elcs[6] + ' ' + str_elcs[7] + ' ' + str_acc1 + ' ' + str_acc2 + ' ' + str_acc3 + ' ' + date + ' ' + str_tst;
            odata << line;
            odata << std::endl;
        } else std::cout << "Unable to open out file!";
        
        // double elc1 = strtodb(str_elc1);
        for (size_t k = 0; k < used_electrod_cnt; ++k)
        {
            electrods[k].push_back(std::stod(str_elcs[k]));
        }
        n++;
    }
    
    auto make_sig = [](const std::vector<double>& electrod) {
        csignal sig;
        std::transform(electrod.cbegin(), electrod.cend(), sig.begin(), [](double val) { return std::complex<double>(val, 0); });
        return sig;
    };

    std::array<csignal, electrod_cnt> sigs;

    for (size_t k = 0; k < used_electrod_cnt; ++k)
    {
        sigs[k] = make_sig(electrods[k]);
    }

    std::array<csignal, electrod_cnt> fftSigns;

    for (size_t k = 0; k < used_electrod_cnt; ++k)
    {
        fftSigns[k] = fourier_transform(sigs[k]);
    }

    for (size_t i = 0; i < fftSigns[0].size(); ++i)
    {
        otrafo << i;
        for (size_t k = 0; k < used_electrod_cnt; ++k)
        {
            otrafo << '\t' << fftSigns[k][i].real();
        }
        otrafo << '\n';
    }
    
    
    inFile.close();
    odata.close();
    otrafo.close();
    

    // csignal cosine(signal_from_generator(leng, gen_cosine(leng/2)));
    // csignal square_wave (signal_from_generator(leng, gen_square_wave(leng / 2)));

    // csignal trans_sqw(fourier_transform(square_wave));
    // std::fill(std::next(std::begin(trans_sqw), 10), std::prev(std::end(trans_sqw), 10), 0);
    // csignal mid(fourier_transform(trans_sqw, true));

    // print_signal(cosine);
    // print_signal(fourier_transform(cosine));
    // print_signal(mid);
    // print_signal(trans_sqw);
    // print_signal(square_wave);
    // print_signal(fourier_transform(square_wave));

    return 0;

}