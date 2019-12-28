#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
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
    

    std::string row, str_elc1, str_elc2, str_elc3, str_elc4, str_elc5, str_elc6, str_elc7, str_elc8, str_acc1, str_acc2, str_acc3, str_tst;
    std::vector<double> electrod1, electrod2, electrod3, electrod4, electrod5, electrod6, electrod7, electrod8;
    std::string date;

    csignal sig1, sig2, sig3, sig4, sig5, sig6, sig7, sig8;

    std::ofstream odata;
    std::ofstream otrafo;

    odata.open("indata.dat");
    otrafo.open("FourierTransformed.dat");

    int n = 0;

    while (inFile >> row >> str_elc1 >> str_elc2 >> str_elc3 >> str_elc4 >> str_elc5 >> str_elc6 >> str_elc7 >> str_elc8 >> str_acc1 >> str_acc2 >> str_acc3 >> date >> str_tst)
    {
        if (odata.is_open())
        {
            std::string line = row + ' ' + str_elc1 + ' ' + str_elc2 + ' ' + str_elc3 + ' ' + str_elc4 + ' ' + str_elc5 + ' ' + str_elc6 + ' ' + str_elc7 + ' ' + str_elc8 + ' ' + str_acc1 + ' ' + str_acc2 + ' ' + str_acc3 + ' ' + date + ' ' + str_tst;
            odata << line;
            odata << std::endl;
        } else std::cout << "Unable to open out file!";
        
        // double elc1 = strtodb(str_elc1);
        electrod1.push_back(std::stod(str_elc1));
        // electrod2[n] = std::stod(str_elc2);
        // electrod3[n] = std::stod(str_elc3);
        // electrod4[n] = std::stod(str_elc4);
        // electrod5[n] = std::stod(str_elc5);
        // electrod6[n] = std::stod(str_elc6);
        // electrod7[n] = std::stod(str_elc7);
        // electrod8[n] = std::stod(str_elc8);
        n++;
    }
    
    std::transform(electrod1.cbegin(), electrod1.cend(), sig1.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod2.cbegin(), electrod2.cend(), sig2.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod3.cbegin(), electrod3.cend(), sig3.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod4.cbegin(), electrod4.cend(), sig4.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod5.cbegin(), electrod5.cend(), sig5.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod6.cbegin(), electrod6.cend(), sig6.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod7.cbegin(), electrod7.cend(), sig7.begin(), [](double val){ return std::complex<double>(val, 0); });
    // std::transform(electrod8.cbegin(), electrod8.cend(), sig8.begin(), [](double val){ return std::complex<double>(val, 0); });

    csignal fftSign1(fourier_transform(sig1));
    // csignal fftSign2(fourier_transform(sig2));
    // csignal fftSign3(fourier_transform(sig3));
    // csignal fftSign4(fourier_transform(sig4));
    // csignal fftSign5(fourier_transform(sig5));
    // csignal fftSign6(fourier_transform(sig6));
    // csignal fftSign7(fourier_transform(sig7));
    // csignal fftSign8(fourier_transform(sig8));

    for (int i = 0; i < fftSign1.size(); ++i)
    {
        otrafo << i << '\t' << fftSign1[i].real() /*<< '\t' << fftSign2[i].real() << '\t' << fftSign3[i].real() << '\t' << fftSign4[i].real() << '\t' << fftSign5[i].real() << '\t' << fftSign6[i].real() << '\t' << fftSign7[i].real() << '\t' << fftSign8[i].real()*/ << '\n';
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