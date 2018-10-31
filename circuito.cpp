#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <limits>
#include "circuito.h"
#include "bool3S.cpp"

using namespace std;

///
///PORTA BASE
///

//CONSTRUTORES
//CONSTRUTOR EXPLICITO
Porta::Porta(unsigned NI)
{
    setNumInputs(NI);
    setSaida(toBool_3S('?'));
}
//CONSTRUTOR POR CÓPIA
Porta::Porta(const Porta &P)
{
    setNumInputs(P.getNumInputs());
    setSaida(P.getSaida());

    for(unsigned i=0; i<Nin; i++)   setId_in(i, P.getId_in(i));
}

//FUNCOES DE CONSULTA
//CONSULTAR ID EM ENTRADA 'i' DA PORTA
int Porta::getId_in(unsigned i) const
{
    if(i < 0 || i >= NUM_MAX_INPUTS_PORTA)
    {
        cerr<<"Id em 'getId_in' invalido";
        return 0;
    }
    return id_in[i];
}

//FUNCOES DE ATRIBUICAO
//ATRIBUI ID 'Id' A ENTRADA 'i' DA PORTA
void Porta::setId_in(unsigned i, int Id)
{
    if(i < 0 || i>=NUM_MAX_INPUTS_PORTA)
    {
        cerr<<"Id em 'setId_in' invalido";
        return;
    }
    id_in[i] = Id;
}
//ATRIBUI NOVO NUMERO DE INPUTS A PORTA (EXCETO NOT)
void Porta::setNumInputs(unsigned N)
{
    Nin = (N >= 2 && N <= NUM_MAX_INPUTS_PORTA ? N : 2);
}
//ATRIBUI VALOR LOGICO 's' A SAIDA DA PORTA
void Porta::setSaida(bool3S s)
{
    saida = s;
}

//FUNCOES DE LEITURA E ESCRITA
//DIGITAR DA PORTA VIA CONSOLE
void Porta::digitar()
{
    int N;
    do
    {
        cout<<"Digite o numero de entradas na porta '"<<getNome()<<"' [2;4]: ";
        cin>>N;

    }while(N < 2 || N> NUM_MAX_INPUTS_PORTA);

    setNumInputs(N);
}
//LER PORTA A PARTIR DE UMA ISTREAM 'I'
//RETORNA FALSE SE IMPOSSIVEL (ERRO NO ARQUIVO)
bool Porta::ler(istream &I)
{
    unsigned NI;
    I >> NI;

    if(NI >=2 && NI<NUM_MAX_INPUTS_PORTA)
    {
        setNumInputs(NI);
        return true;
    }
    return false;
}
//IMPRIMIR PORTA NA OSTREAM 'O'
//VALIDO PARA CONSOLE E ARQUIVO
ostream &Porta::imprimir(ostream &O) const
{
    O << getNome() + " ";
    O << Nin + ": ";

    for(unsigned i=0; i<Nin; i++) (i != Nin-1 ? O << getId_in(i) + " " : O << getId_in(i));

    return O;
}



///
///PORTAS ESPECÍFICAS
///

//PORTA NOT
//ATRIBUI NUMERO DE INPUTS PARA PORTA 'NOT'
//FUNCAO POLIMORFICA. 'Nin' SEMPRE SERA == 1
void Porta_NOT::setNumInputs(unsigned N)
{
    (N == 1 ? Nin = N : Nin = 1);
}
//DIGITA UMA PORTA 'NOT'
//FUNCAO POLIMORFICA. NUMERO DE INPUTS == 1
void Porta_NOT::digitar()
{
    setNumInputs(1);
}
//LE UMA PORTA NOT
//FUNCAO POLIMORFICA. 'FALSE' SE NI != 1
bool Porta_NOT::ler(istream &I)
{
    int NI;
    I >> NI;

    return (NI == 1);
}
//SIMULA PORTA 'NOT'
bool3S Porta_NOT::simular(const bool3S in[])
{
    return ~in[0];
}

//PORTA AND
//SIMULA PORTA AND COM 'Nin' ENTRADAS
bool3S Porta_AND::simular(const bool3S in[])
{
    bool3S out = in[0];
    for(unsigned i=1; i<Nin; i++)  out = out&in[i];

    return out;
}

//PORTA NAND
//SIMULA PORTA NAND COM 'Nin' ENTRADAS
bool3S Porta_NAND::simular(const bool3S in[])
{
    bool3S out = in[0];
    for(unsigned i=1; i<Nin; i++)  out = out&in[i];

    return ~out;
}

//PORTA OR
//SIMULA PORTA OR COM 'Nin' ENTRADAS
bool3S Porta_OR::simular(const bool3S in[])
{
    bool3S out = in[0];
    for(unsigned i=1; i<Nin; i++)  out = out|in[i];

    return out;
}

//PORTA NOR
//SIMULA PORTA NOR COM 'Nin' ENTRADAS
bool3S Porta_NOR::simular(const bool3S in[])
{
    bool3S out = in[0];
    for(unsigned i=1; i<Nin; i++)  out = out|in[i];

    return ~out;
}

//PORTA XOR
//SIMULA PORTA XOR COM 'Nin' ENTRADAS
bool3S Porta_XOR::simular(const bool3S in[])
{
    bool3S out = in[0];
    for(unsigned i=1; i<Nin; i++)  out = out^in[i];

    return out;
}

//PORTA NXOR
//SIMULA PORTA NXOR COM 'Nin' ENTRADAS
bool3S Porta_NXOR::simular(const bool3S in[])
{
    bool3S out = in[0];
    for(unsigned i=1; i<Nin; i++)  out = out^in[i];

    return ~out;
}

///
///CIRCUITO
///

//ALOCA ESPACO PARA OS VETORES DO CIRCUITO
void Circuito::alocar(unsigned NI, unsigned NO, unsigned NP)
{
    if(NI >= 0) inputs.resize(NI);
    if(NO >= 0) id_out.resize(NO);
    if(NP >= 0) portas.resize(NP);
}
//CONSTRUTOR POR COPIA DO CIRCUITO
void Circuito::copiar(const Circuito &C)
{
    if(&C != this)
    {
        inputs = C.inputs;
        id_out = C.id_out;
        portas = C.portas;
    }
}
//LIMPA OS VETORES DO CIRCUITO
void Circuito::limpar()
{
    inputs.clear();
    id_out.clear();
    portas.clear();
}
//RETORNA A SIGLA DA PORTA NO VETOR 'portas' DE ID 'IdPorta'
string Circuito::getNomePorta(unsigned IdPorta) const
{
    if(IdPorta < 1 || IdPorta > getNumPortas())
    {
        cerr<<"Nao pode buscar nome da porta. (Id invalido)";
        return 0;
    }
    return portas[IdPorta-1]->getNome();
}
//RETORNA NUMERO DE ENTRADAS NA PORTA DE ID 'IdPorta'
unsigned Circuito::getNumInputsPorta(unsigned IdPorta) const
{
    if(IdPorta < 1 || IdPorta > getNumPortas())
    {
        cerr<<"Nao pode buscar Num Inputs na porta. (Id invalido)";
        return 0;
    }
    return portas[IdPorta-1]->getNumInputs();
}
//RETORNA O ID INSERIDO NA ENTRADA 'i' DA PORTA COM ID 'IdPorta'
int Circuito::getId_inPorta(unsigned IdPorta, unsigned i) const
{
    if(IdPorta < 1 || IdPorta > getNumPortas())
    {
        cerr<<"Nao pode buscar Id na porta. (Id invalido)";
        return 0;
    }
    return portas[IdPorta-1]->getId_in(i);
}
//RETORNA O VALOR LOGICO DA SAIDA COM ID 'IdOut'
bool3S Circuito::getSaida(unsigned IdOut) const
{
    IdOut -= 1;
    if(IdOut < 0 || IdOut >= getNumOutputs())
    {
        cerr<<"Nao pode buscar saida. (Id invalido)";
        return toBool_3S('?');
    }

    //VAI AGIR DIFERENTE DEPENDENDO DO VALOR DA ORIGEM
    int origem = getIdOutput(IdOut);

    //SE ORIGEM == 0 RETORNA UNDEF_3S
    if(origem == 0)
    {
        cerr<<"Origem com index '0' inexistente.";
        return toBool_3S('?');
    }

    //SE ORIGEM < 0 RETORNA VALOR DA ENTRADA DO CIRCUITO
    if(origem < 0)  return inputs[(origem+1)*(-1)];

    //SE ORIGEM > 0 RETORNA VALOR DA SAIDA DE UMA PORTA
    if(origem > 0)  return portas[origem-1]->getSaida();

}
//RETORNA ID ARMAZENADO NA SAIDA DE ID 'idOut'
int Circuito::getIdOutput(unsigned IdOut) const
{
    return id_out[IdOut];
}
//VERIFICA SE CIRCUITO ALOCADO EH VALIDO
//USADO ANTES DE PEDIR SIMULACAO
bool Circuito::valido() const
{
    //TRANFORMANDO UNDEF -> INT
    int ninputs = getNumInputs();
    int nportas = getNumPortas();

    //VERIFICA SE OS VETORES ESTAO ALOCADOS
    if(getNumInputs() == 0)
    {
        cerr<<"Vetor de inputs nao alocado!"<<endl;
        return false;
    }
    if(getNumOutputs() == 0)
    {
        cerr<<"Vetor de outputs nao alocado!"<<endl;
        return false;
    }
    if(getNumPortas() == 0)
    {
        cerr<<"Vetor de portas nao alocado!"<<endl;
        return false;
    }

    //VERIFICA SE SAIDAS ESTAO PREENCHIDAS E SAO VALIDAS
    for(unsigned i=0; i<getNumOutputs(); i++)
    {
        if(id_out[i] == 0 || id_out[i] < -ninputs || id_out[i] > nportas)
        {
            cerr<<"Outputs nao totalmente definidos ou mal conectados.";
            return false;
        }
    }

    //VERIFICA SE PORTAS ESTÃO PREENCHIDAS E VALIDAS
    for(unsigned i=0; i<getNumPortas(); i++) {
       for(unsigned j=0; j<portas[i]->getNumInputs(); j++)
        {
            if(portas[i] == NULL)
            {
                cerr<<"Portas nao totalmente definidas.";
                return false;
            }

            if(portas[i]->getId_in(j) == 0 || portas[i]->getId_in(j) < -ninputs || portas[i]->getId_in(j) > nportas)
            {
                cerr<<"Portas conectadas incorretamente.";
                return false;
            }
        }
    }
    return true;
}
//TORNA PORTA DE ID 'IdPorta' NOVA PORTA COM SIGLA 'T' E NUMERO DE ENTRADAS 'Nin'
void Circuito::setPorta(unsigned IdPorta, const string &T, unsigned NIn)
{
    if(T != "NT" && T != "AN" && T != "NA"
       && T != "OR" && T != "NO" && T != "XO" && T != "NX") return;

    IdPorta--;

    (T == "NT" ? portas[IdPorta] = new Porta_NOT() :
    (T == "AN" ? portas[IdPorta] = new Porta_AND() :
    (T == "NA" ? portas[IdPorta] = new Porta_NAND() :
    (T == "OR" ? portas[IdPorta] = new Porta_OR() :
    (T == "NO" ? portas[IdPorta] = new Porta_NOR() :
    (T == "XO" ? portas[IdPorta] = new Porta_XOR() :
                 portas[IdPorta] = new Porta_NXOR()))))));

    portas[IdPorta]->setNumInputs(NIn);
}
//ATRIBUI ENTRADA 'I' DA PORTA COM ID 'IdPorta' O ID 'Id'
void Circuito::setId_inPorta(unsigned IdPorta, unsigned I, int Id) const
{
    if(IdPorta > getNumPortas())
    {
        cerr<<"IdPorta em 'setId_inPorta' invalido (> getNumPortas())";
        return;
    }
    if(Id < -getNumInputs() || Id > getNumPortas())
    {
        cerr<<"Id em 'setId_inPorta' invalido";
        return;
    }

    portas[IdPorta-1]->setId_in(I,Id);
}
//ATRIBUI ID 'Id' AO OUTPUT DE ID 'IdOut'
void Circuito::setIdOutput(unsigned IdOut, int Id)
{
    if(IdOut > getNumOutputs())
    {
        cerr<<"IdOut em 'setIdOutput' invalido (> getNumOutputs())";
        return;
    }

    int prov = getNumInputs();
    prov = -prov;

    if(Id < prov || Id > getNumPortas())
    {
        cerr<<"Id em 'setIdOutput' invalido";
        return;
    }

    id_out[IdOut-1] = Id;
}
//DIGITA CIRCUITO VIA TECLADO PARA APLICACOES VIA CONSOLE
void Circuito::digitar()
{
    //DIMENSIONANDO O CIRCUITO
    int NI=1, NO=1, NP=1, Nin=1, prov, prov2;
    string porta;

    do
    {
        cout<<"Digite o numero de entradas no circuito: ";
        cin>>NI;
    }while(NI <=0);

    do
    {
        cout<<"Digite o numero de saidas no circuito: ";
        cin>>NO;
    }while(NO <=0);

    do
    {
        cout<<"Digite o numero de portas no circuito: ";
        cin>>NP;
    }while(NP <=0);

    redimensionar(NI,NO,NP);

    //CONECTANDO TODAS AS SAIDAS
    for(unsigned i=0; i<getNumPortas(); i++)
    {
        cout<<"Digite a sigla da porta (ID="<<i+1<<") que deseja criar: ";
        cin>>porta;

        setPorta(i+1,porta,1);
        if(porta == "NT") continue;

        portas[i]->digitar();
    }

    //CONECTANDO TODAS AS ENTRADAS DAS PORTAS
    for(unsigned i=0; i<getNumOutputs(); i++)
    {
        do
        {
            cout<<"Digite o ID da porta ou entrada conectada ao output ("<<i+1<<" do circuito: ";
            cin>>id_out[i];

            prov = getNumInputs();
            prov2 = getNumPortas();
            prov = -prov;

        } while(id_out[i] == 0 || id_out[i] < prov || id_out[i] > prov2);
    }

    for(unsigned i=0; i<getNumPortas(); i++)
    {
        for(unsigned j=0; j<portas[i]->getNumInputs(); j++)
        {
            int id;
            do
            {
                cout<<"Digite o ID da entrada ("<<j+1<<"/"<<portas[i]->getNumInputs()<<") ";
                cout<<"da porta "<<portas[i]->getNome()<<" numero "<<i+1<<": ";
                cin>>id;

                prov = getNumInputs();
                prov2 = getNumPortas();
                prov = -prov;

            } while(id == 0 || id < prov || id > prov2);

            portas[i]->setId_in(j, id);
        }
    }
}
//LE CIRCUITO DE ARQUIVO
bool Circuito::ler(const string &arq)
{
    limpar();
    ifstream doc(arq.c_str());

    if (doc.is_open())
    {
        string prov;
        char chr, chr2;
        int NI, NO, NP, index, idIn;

        doc >> prov;
        if (prov != "CIRCUITO:")    {limpar();   return false;}

        doc >> NI;
        if (NI < 1)        {limpar();   return false;}
        doc >> NO;
        if (NO < 1)        {limpar();   return false;}
        doc >> NP;
        if (NP < 1)        {limpar();   return false;}

        redimensionar(NI,NO,NP);

        doc >> prov;
        if (prov != "PORTAS:")  {limpar();   return false;}

        for(unsigned i = 1; i<= getNumPortas(); i++)
        {

            doc >> index;
            if(index != i)  {limpar();   return false;}

            doc.ignore(numeric_limits<streamsize>::max(), ')');

            doc >> prov;

            if(prov != "NT" && prov != "AN" && prov != "NA"
               && prov != "OR" && prov != "NO" && prov != "XO" && prov != "NX") {limpar();   return false;}

            setPorta(i, prov, 1);

            doc.ignore(numeric_limits<streamsize>::max(), ' ');

            if(!portas[i-1]->ler(doc))  {limpar();   return false;}

            doc.ignore(numeric_limits<streamsize>::max(), ' ');

            for(unsigned j = 0; j < portas[i-1]->getNumInputs(); j++)
            {
                doc >> idIn;

                if(idIn == 0)        {limpar();   return false;}
                if(idIn < 0)    if(abs(idIn) > getNumInputs())    {limpar();   return false;}
                if(idIn > 0)    if(idIn > getNumPortas())     {limpar();   return false;}

                portas[i-1]->setId_in(j,idIn);
            }
        }

        doc >> prov;
        if (prov != "SAIDAS:")  {limpar();   return false;}

        for(unsigned i = 1; i <= getNumOutputs(); i++)
        {
            doc >> index;
            if(index != i)  {limpar();   return false;}
            doc.ignore(numeric_limits<streamsize>::max(), ' ');

            doc >> idIn;

            if(idIn == 0)   {limpar();   return false;}
            if(idIn < 0)    if(abs(idIn) > getNumInputs())    {limpar();   return false;}
            if(idIn > 0)    if(idIn > getNumPortas()) {limpar();   return false;}

            setIdOutput(i, idIn);
        }
        doc.close();
        return true;

    } else {
        cerr<<"Erro na abertura do arquivo "<<arq<<" para leitura!";
        return false;
    }
}
//IMPRIME CIRCUITO EM OSTREAM 'O'
ostream &Circuito::imprimir(ostream &O) const
{
    O <<"CIRCUITO: " << getNumInputs() << " ";
    O << getNumOutputs() << " " << getNumPortas() << endl;

    O <<"PORTAS:"<<endl;

    for(unsigned i=0; i < getNumPortas(); i++)
    {
        O << i+1 << ") " << portas[i]->getNome() << " " << portas[i]->getNumInputs() <<": ";
        for(unsigned j = 0; j < portas[i]->getNumInputs(); j++)
        {
            O << portas[i]->getId_in(j) << " ";
        }
        O << endl;
    }

    O <<"SAIDAS:"<<endl;
    for(unsigned i=0; i < getNumOutputs(); i++)   O << i+1 << ") " << id_out[i] << endl;

    return O;
}
//SALVA CIRCUITO EM ARQUIVO (CHAMA FUNCAO IMPRIMIR EM OSTREAM 'O')
bool Circuito::salvar(const string &arq) const
{
    ofstream doc(arq.c_str());
    if(doc.is_open())
    {
        imprimir(doc);
    } else {
        cerr<<"Erro na abertura do arquivo "<<arq<<" para escrita!";
        return false;
    }
    return true;
}
//ATRIBUI ENTRADAS LOGICAS AO CIRCUITO CASO O MESMO SEJA VALIDO
//FUNCAO USADA SOMENTE PARA CONSOLE
void Circuito::digitarEntradas()
{
    if(valido())
    {
        char prov;
        cout<<"(T) Verdadeiro | (F) Falso | (?) Indefinido"<<endl;
        for(unsigned i = 0; i < inputs.size(); i++)
        {
            prov = 'X';
            do
            {
                cout<<"Digite o valor logico da entrada ["<<i+1<<"/"<<getNumInputs()<<"] : "<<endl;
                cin>>prov;

            } while(prov!='T' && prov!='F' && prov!='?');

            inputs[i] = toBool_3S(prov);
        }
    } else {
        cerr<<"Circuito invalido! Impossivel imprimir!"<<endl;
        return;
    }
}
//IMPRIME AS ESTRADAS DO CIRCUITO
void Circuito::imprimirEntradas(void) const
{
    if(valido())
    {
        cout<<"Entrada: ";
        for(unsigned i = 0; i < getNumInputs(); i++) cout<<inputs[i]<<" ";

    } else {
        cerr<<"Circuito invalido! Impossivel imprimir!"<<endl;
        return;
    }
}
//IMPRIME AS SAIDAS DO CIRCUITO
void Circuito::imprimirSaidas(void) const
{
    if(valido())
    {
        cout<<" Saida: ";
        for(unsigned i = 0; i < getNumOutputs(); i++)
        {
            if(id_out[i] < 0)
            {
                cout<<inputs[abs(id_out[i]+1)]<<" ";
            } else {
                cout<<portas[id_out[i]-1]->getSaida()<<" ";
            }
        }
    } else {
        cerr<<"Circuito invalido! Impossivel imprimir!"<<endl;
        return;
    }
}
//CHAMA SIMULACAO PARA O CIRCUITO ALOCADO E IMPRIME SAIDAS
void Circuito::simular()
{
    if(simular(inputs))
    {
        cout<<"Simulacao completa!"<<endl;
        cout<<"Resultado: ";
        imprimirSaidas();

    } else {
        cerr<<"Erro ao tentar simular!"<<endl;
    }
}
//SIMULA SAIDAS DAS PORTAS E SAIDAS PELOS VALORES LOGICOS PASSADOS COMO PARAMETRO
bool Circuito::simular(vector<bool3S> Inputs)
{
    bool tudo_def;
    bool alguma_def;
    imprimirEntradas();

    for(unsigned i=0; i < getNumPortas(); i++)  portas[i]->setSaida(toBool_3S('?'));

    do
    {
        tudo_def = true;
        alguma_def = false;

        for(unsigned i=0; i < getNumPortas(); i++)
        {
            if(portas[i]->getSaida() == toBool_3S('?'))
            {
                int NinPorta = portas[i]->getNumInputs();
                bool3S in_porta[NinPorta];

                for(unsigned j=0; j<NinPorta; j++)
                {
                    int id = getId_inPorta(i+1, j);

                    if(id == 0)
                    {
                        cerr<<"Erro na leitura do array de bool3S. Id_in == 0.";
                        return false;
                    }
                    if(id > 0)  in_porta[j] = portas[id-1]->getSaida();
                    if(id < 0)  in_porta[j] = inputs[abs(id+1)];

                }

                portas[i]->setSaida(portas[i]->simular(in_porta));

                if(portas[i]->getSaida() == toBool_3S('?'))
                {
                    tudo_def = false;
                } else {
                    alguma_def = true;
                }
            }
        }
    } while (!tudo_def && alguma_def);

    imprimirSaidas();
    cout<<endl;
    return true;
}
//GERA TABELA DA VERDADE A PARTIR DE TODAS AS COMBINACOES DE INPUTS NO CIRCUITO
//CIRCUITO DEVE ESTAR ALOCADO E VALIDO PARA SIMULAR
void Circuito::gerarTabela(void)
{
    int i;
    for(unsigned j = 0; j < getNumInputs(); j++)    inputs[j] = toBool_3S('F');

    do
    {
        simular(inputs);
        i = getNumInputs() - 1;

        while(i >= 0 && inputs[i] == toBool_3S('?'))
        {
            inputs[i] = toBool_3S('F');
            i--;
        }

        if(i >= 0)
        {
            if (inputs[i] == toBool_3S('F'))
            {
                inputs[i] = toBool_3S('T');
            } else {
                inputs[i] = toBool_3S('?');
            }
        }
    } while (i >= 0);
}
