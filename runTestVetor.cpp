//
// Created by msobral on 22/11/2022.
//

//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include "vetor.h"
#include "gtest/gtest.h"

using namespace std;

class TesteDynarray: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }

    void escreva_lista(const list<int> & l, const string & sep, ostream & out) {
        if (l.empty()) return;
        int n = l.size();
        auto it=l.begin();
        for (; n > 1; it++, n--) out << *it << sep;
        out << *it;
    }

};

TEST_F(TesteDynarray, CriarVazio) {
    auto v = prg2::vetor_cria<int>();
    ASSERT_TRUE(prg2::vetor_vazio(v));
    ASSERT_EQ(prg2::vetor_tamanho(v), 0);
    ASSERT_EQ(prg2::vetor_capacidade(v), prg2::MinSize);
}

TEST_F(TesteDynarray, DestroiArray) {
    auto v = prg2::vetor_cria<double>();
    ASSERT_NO_THROW(prg2::vetor_destroi(v));
}

TEST_F(TesteDynarray, AnexarSemExpandir) {
    auto v = prg2::vetor_cria<float>();

    for (auto j=0; j < prg2::MinSize; j++) {
        prg2::vetor_anexa(v, j*1.0f);
        ASSERT_FALSE(prg2::vetor_vazio(v));
        ASSERT_EQ(prg2::vetor_tamanho(v), j+1);
    }
}

TEST_F(TesteDynarray, InserirSemExpandir) {
    auto v = prg2::vetor_cria<long>();

    for (auto j=0; j < prg2::MinSize; j++) {
        prg2::vetor_insere(v, j*1l);
        ASSERT_FALSE(prg2::vetor_vazio(v));
        ASSERT_EQ(prg2::vetor_tamanho(v), j+1);
    }
}

TEST_F(TesteDynarray, FrenteVazio) {
    auto v = prg2::vetor_cria<string>();

    ASSERT_THROW(prg2::vetor_frente(v), std::invalid_argument);
}

TEST_F(TesteDynarray, AtrasVazio) {
    auto v = prg2::vetor_cria<double>();

    ASSERT_THROW(prg2::vetor_atras(v), std::invalid_argument);
}

TEST_F(TesteDynarray, AnexarAcessar) {
    auto v = prg2::vetor_cria<int>();
    const int Val = 5;

    for (auto j=0; j < prg2::MinSize; j++) {
        prg2::vetor_anexa(v, j+Val);
        ASSERT_EQ(prg2::vetor_atras(v), j+Val);
    }
}

TEST_F(TesteDynarray, InserirAcessar) {
    auto v = prg2::vetor_cria<long>();
    const int Val = 5;

    for (long j=0; j < prg2::MinSize; j++) {
        prg2::vetor_insere(v, j+Val);
        ASSERT_EQ(prg2::vetor_frente(v), j+Val);
    }
}

TEST_F(TesteDynarray, AnexarComExpansao) {
    auto v = prg2::vetor_cria<float>();

    for (auto j=0; j < 2*prg2::MinSize; j++) {
        prg2::vetor_anexa(v, j*1.0f);
        ASSERT_EQ(prg2::vetor_atras(v), j*1.0f);
        ASSERT_EQ(prg2::vetor_tamanho(v), j+1);
        ASSERT_EQ(prg2::vetor_capacidade(v), prg2::MinSize*ceilf((float)(j+1)/prg2::MinSize));
    }
}

TEST_F(TesteDynarray, InserirComExpansao) {
    auto v = prg2::vetor_cria<double>();

    for (auto j=0; j < 2*prg2::MinSize; j++) {
        prg2::vetor_insere(v, j*1.0);
        ASSERT_EQ(prg2::vetor_frente(v), j*1.0);
        ASSERT_EQ(prg2::vetor_tamanho(v), j+1);
        ASSERT_EQ(prg2::vetor_capacidade(v), prg2::MinSize*ceilf((float)(j+1)/prg2::MinSize));
    }
}

TEST_F(TesteDynarray, AnexarIterar) {
    auto v = prg2::vetor_cria<string>();
    const int Val = 7;

    for (auto j=0; j < 2*prg2::MinSize; j++) {
        prg2::vetor_anexa(v, to_string(j+Val));
    }
    for (auto j=0; j < 2*prg2::MinSize; j++) {
        ASSERT_EQ(prg2::vetor_obtem(v, j), to_string(j+Val));
    }

    // posição inválida
    ASSERT_THROW(prg2::vetor_obtem(v, 100), std::invalid_argument);
    ASSERT_THROW(prg2::vetor_obtem(v, prg2::vetor_tamanho(v)), std::invalid_argument);
}

TEST_F(TesteDynarray, InserirIterar) {
    auto v = prg2::vetor_cria<int>();
    const int Val = 7;

    for (auto j=0; j < 2*prg2::MinSize; j++) {
        prg2::vetor_insere(v, j+Val);
    }
    int val = -1 + 2*prg2::MinSize + Val;
    for (auto j=0; j < 2*prg2::MinSize; j++) {
        ASSERT_EQ(prg2::vetor_obtem(v, j), val--);
    }
}

TEST_F(TesteDynarray, Limpa) {
    auto v = prg2::vetor_cria<long>();

    for (long j = 0; j < 2 * prg2::MinSize; j++) {
        prg2::vetor_insere(v, j);
    }
    ASSERT_FALSE(prg2::vetor_vazio(v));
    prg2::vetor_limpa(v);
    ASSERT_TRUE(prg2::vetor_vazio(v));
    ASSERT_EQ(prg2::vetor_tamanho(v), 0);
}

TEST_F(TesteDynarray, RemoveInicio) {
    auto v = prg2::vetor_cria<int>();
    ASSERT_THROW(prg2::vetor_remove_inicio(v), std::invalid_argument);

    for (auto j=0; j < prg2::MinSize; j++) {
        prg2::vetor_anexa(v, j);
    }
    for (auto j=0; j < prg2::MinSize; j++) {
        ASSERT_EQ(prg2::vetor_frente(v), j);
        prg2::vetor_remove_inicio(v);
        ASSERT_EQ(prg2::vetor_tamanho(v), prg2::MinSize-(j+1));
    }
}

TEST_F(TesteDynarray, RemoveFim) {
    auto v = prg2::vetor_cria<int>();
    ASSERT_THROW(prg2::vetor_remove_fim(v), std::invalid_argument);

    for (auto j=0; j < prg2::MinSize; j++) {
        prg2::vetor_insere(v, j);
    }
    for (auto j=0; j < prg2::MinSize; j++) {
        ASSERT_EQ(prg2::vetor_atras(v), j);
        prg2::vetor_remove_fim(v);
        ASSERT_EQ(prg2::vetor_tamanho(v), prg2::MinSize-(j+1));
    }
}

TEST_F(TesteDynarray, InserePosicao) {
    auto v = prg2::vetor_cria<int>();

    for (auto j = 0; j < prg2::MinSize/2; j++) {
        prg2::vetor_insere(v, j);
    }
    auto len = prg2::vetor_tamanho(v);
    // no meio
    prg2::vetor_insere(v, len/2, 11);
    ASSERT_EQ(prg2::vetor_obtem(v, len/2), 11);
    ASSERT_EQ(prg2::vetor_tamanho(v), len+1);

    // no inicio
    prg2::vetor_insere(v, 0, 55);
    ASSERT_EQ(prg2::vetor_frente(v), 55);
    ASSERT_EQ(prg2::vetor_tamanho(v), len+2);

    // no final
    //    prg2::vetor_insere(v, 11, len);
    //    ASSERT_EQ(prg2::vetor_atras(v), 77);
    //    ASSERT_EQ(prg2::vetor_tamanho(v), len+3);

    // posição inválida
    ASSERT_THROW(prg2::vetor_insere(v, 2*len, 11), std::invalid_argument);
    //    ASSERT_EQ(prg2::vetor_atras(v), 77);
    //    ASSERT_EQ(prg2::vetor_tamanho(v), len+3);

}