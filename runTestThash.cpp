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
#include "thash.h"
#include "gtest/gtest.h"

using namespace std;

class TesteThash: public ::testing::Test {
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

TEST_F(TesteThash, CriarVazio) {
    auto v = prg2::thash_cria<string,int>();
    ASSERT_TRUE(prg2::thash_vazio(v));
    ASSERT_EQ(prg2::thash_tamanho(v), 0);
}

TEST_F(TesteThash, DestroiArray) {
    auto v = prg2::thash_cria<string,float>();
    ASSERT_NO_THROW(prg2::thash_destroi(v));
}

TEST_F(TesteThash, Adicionar) {
    auto v = prg2::thash_cria<int,string>();

    for (auto j=0; j < 10; j++) {
        auto val = to_string(j);
        prg2::thash_adiciona(v, j, val);
        ASSERT_FALSE(prg2::thash_vazio(v));
        ASSERT_EQ(prg2::thash_tamanho(v), j+1);
        ASSERT_EQ(prg2::thash_obtem(v, j), val);
    }
}

TEST_F(TesteThash, ObtemVazio) {
    auto v = prg2::thash_cria<float,int>();

    ASSERT_THROW(prg2::thash_obtem(v, 2.7828f), std::invalid_argument);
}

TEST_F(TesteThash, Existe) {
    auto v = prg2::thash_cria<long,int>();

    thash_adiciona(v, 100l, 1);
    thash_adiciona(v, 200l, 2);
    thash_adiciona(v, 300l, 3);
    ASSERT_EQ(prg2::thash_existe(v, 100l), true);
    ASSERT_EQ(prg2::thash_existe(v, 200l), true);
    ASSERT_EQ(prg2::thash_existe(v, 300l), true);
    ASSERT_EQ(prg2::thash_existe(v, 301l), false);
}

TEST_F(TesteThash, Obtem) {
    auto v = prg2::thash_cria<string,int>();

    thash_adiciona(v, "um"s, 1);
    thash_adiciona(v, "dois"s, 2);
    thash_adiciona(v, "tres"s, 3);
    ASSERT_EQ(prg2::thash_obtem(v, "um"s), 1);
    ASSERT_EQ(prg2::thash_obtem(v, "dois"s), 2);
    ASSERT_EQ(prg2::thash_obtem(v, "tres"s), 3);
    ASSERT_THROW(prg2::thash_obtem(v, "quatro"s), std::invalid_argument);
}

TEST_F(TesteThash, Remove) {
    auto v = prg2::thash_cria<double,int>();

    thash_adiciona(v, 1.1, 1);
    thash_adiciona(v, 2.2, 2);
    thash_adiciona(v, 3.3, 3);
    ASSERT_NO_THROW(prg2::thash_remove(v, 1.1));
    ASSERT_EQ(prg2::thash_existe(v, 1.1), false);
    ASSERT_EQ(prg2::thash_tamanho(v), 2);
    ASSERT_NO_THROW(prg2::thash_remove(v, 2.2));
    ASSERT_EQ(prg2::thash_existe(v, 2.2), false);
    ASSERT_EQ(prg2::thash_tamanho(v), 1);
}

TEST_F(TesteThash, Expandir) {
    auto v = prg2::thash_cria<double,int>();

    for (auto j=0; j < 100; j++) {
        auto chave = to_string(j);
        prg2::thash_adiciona(v, j*1.01, j);
        ASSERT_EQ(prg2::thash_tamanho(v), j+1);
        ASSERT_EQ(prg2::thash_obtem(v, j*1.01), j);
    }
}
