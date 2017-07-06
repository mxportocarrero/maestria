#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
typedef std::vector< std::string > vstring;
typedef std::vector<int> vint;
typedef std::vector< std::vector<int> > mInt; // matrix de enteros

bool find(int x, vint & vec){
    if (vec.size() == 0) return 0;
    for(auto i:vec)
        if(i == x) return 1;
    return 0;
}

bool insert(int x, vint& vec){
    if(find(x,vec)) return 0;
    vec.push_back(x);
    return 1;
}

int myAtoi(const char & c){return c - '0';}

int getMinGreedyDistance(const mInt & distances){
    int n = distances.size();
    int actualCity = 0;
        vint travel = {0};
        int nextCity;
        int totalDistance = 0;

        for(int i = 0; i < n-1; i++){ // bucle que inserta las n ciudades
            int minDistance = 10000;
            int minCity = 0;

                for(int j = 0; j < n; j++){
                    if(j != actualCity && !find(j,travel) && minDistance > distances[actualCity][j]){
                        minDistance = distances[actualCity][j];
                        minCity = j;
                    }
                }
                totalDistance += distances[actualCity][minCity];
                actualCity = minCity;
                travel.push_back(actualCity);
        }
        //for(auto x : travel) std::cout << x << " ";
        //std::cout<< totalDistance << "||";
        return totalDistance;

}


class GreedyTravellingSalesman{
public:
    int worstDistance(vstring thousands, vstring hundreds, vstring tens, vstring ones){
        int n = thousands.size();
        mInt distances;
        vint partialDistances;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n ;j++){
                int x = myAtoi(thousands[i][j]) * 1000 + myAtoi(hundreds[i][j])*100 + myAtoi(tens[i][j])*10+myAtoi(ones[i][j]);
                partialDistances.push_back(x);
            }
            distances.push_back(partialDistances);
            partialDistances.clear();
        } // fin del bucle for
/*
        for(auto x : distances){
            for(auto y : x) std::cout << y << " ";
            std::cout << std::endl;
        }*/

        vint valuesToCompare(1000,0);
        valuesToCompare[0] = 1;valuesToCompare[1]=9999;

        int totalMaxDistance = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n ;j++) if(i!=j) {
                int tmp = distances[i][j];
                int valuesCount = 2;

/*
                        vint tmpVector = distances[i];
                        sort(tmpVector.begin(),tmpVector.end());
                        for(auto x : tmpVector){
                            std::cout << x << " ";
                        }
                        std::cout << std::endl;

                        distances[i][j] = tmpVector[2];
                        if(totalMaxDistance < getMinGreedyDistance(distances)) totalMaxDistance = getMinGreedyDistance(distances);

                        distances[i][j] = tmp +1;
                        if(totalMaxDistance < getMinGreedyDistance(distances)) totalMaxDistance = getMinGreedyDistance(distances);

                        distances[i][j] = 9999;
                        if(totalMaxDistance < getMinGreedyDistance(distances)) totalMaxDistance = getMinGreedyDistance(distances);
                        distances[i][j] = 1;
                        if(totalMaxDistance < getMinGreedyDistance(distances)) totalMaxDistance = getMinGreedyDistance(distances);
                        */

                for(int k = 0; k < n;k++)
                    if(k != i && k != j){
                        if(distances[i][k]>1)valuesToCompare[valuesCount++] = distances[i][k] -1;
                        if(distances[i][k]<9999)valuesToCompare[valuesCount++] = distances[i][k] +1;
                        if(distances[i][k]>0)valuesToCompare[valuesCount++] = distances[i][k];
                    }

                for(int x = 0; x < valuesCount; x++){
                    distances[i][j] = valuesToCompare[x];
                    int totTmp = getMinGreedyDistance(distances);
                    if(totalMaxDistance < totTmp) {
                            totalMaxDistance = totTmp;
                    }
                }

                distances[i][j] = tmp;

            }
        }
        std::cout << totalMaxDistance;
    }
};


int main(){

/*
    vstring thousands = {"055", "505", "550"};
    vstring hundreds = {"000", "000", "000"};
    vstring tens = {"000", "000", "000"};
    vstring ones = {"000", "000", "000"};
*/
/*
    vstring thousands = {"018", "101", "990"};
    vstring hundreds = {"000", "000", "990"};
    vstring tens = {"000", "000", "990"};
    vstring ones = {"000", "000", "990"};
*/
/*
    vstring thousands ={"00888", "00999", "00099", "00009", "00000"};
    vstring hundreds ={"00000", "00999", "00099", "00009", "00000"};
    vstring tens ={"00000", "10999", "11099", "11109", "11110"};
    vstring ones ={"01000", "00999", "00099", "00009", "00000"};
*/
/*
vstring thousands = {"000000", "000000", "990999", "999099", "999909", "999990"};
vstring hundreds = {"000000", "000000", "990999", "999099", "999909", "999990"};
vstring tens = {"000000", "000000", "990999", "999099", "999909", "999990"};
vstring ones = {"011111", "101111", "990998", "999099", "999809", "999980"};
*/
/*
    vstring thousands ={"0329", "2036", "2502", "8970"};
    vstring hundreds ={"0860", "5007", "0404", "2770"};
    vstring tens ={"0111", "2087", "2009", "2670"};
    vstring ones ={"0644", "1094", "7703", "7550"};
*/

vstring thousands = {"098444156277392825243100607342", "200097656837707947798866622385", "290231695687128834848596019656", "407026565077650435591867333275", "843401002617957470339040852874", "349970591997218853400632158696", "419933000593511123878416328483", "696294503254214847884399055978", "641473980706392541888675375279", "936720077098054565078142449625", "203476089500970673371115103717", "511071853860312304204656816567", "347105714685052402147763392257", "125122220860203856679947732062", "121462979669220132944063071653", "928254504048223043681383050365", "502607124708785202536036594373", "793596587517012870906900400361", "712360060935346182084840996318", "761671392040312345002273366240", "812935320276738878200716148806", "228506917464479046839069740872", "755395721473881083093906155745", "192597782177910118061710039501", "721382839206745793530453013267", "076061794267810491768114700256", "857528357758085424372388710251", "173322450800442594145600093043", "761667192345925280210514410800", "521229810525064090301842864060"};
vstring hundreds = {"098270581534726237580246464451", "108829763716747148395013332067", "830061279541380758964430491222", "431005058477371114834129826284", "601807314489142917339949914290", "330640126699733151822328009407", "851821069798846354566780680271", "648888407535627630663351884365", "051398660825518466890170447894", "631934884097214069747147155777", "768071219404930950472885304916", "924954163330715847561718395488", "189910033179029204426829479070", "960645776060701332402794474433", "244875842263950931884758650019", "528470075229660077692189442311", "752198673046476808978058423064", "899325998610605600525587569431", "965750123741820904031880230236", "121658852172052167706008445728", "556199378085507717770434101126", "864838242791403197110088834005", "593435343245223500439707230479", "622529771475840345624500421425", "503486612623475041392122088159", "518334626169655694269507400008", "967091631529233593414345370288", "300474162107271438029222620086", "010527691044447729596127150108", "742822904991333205419603623270"};
vstring tens = {"029421809872798033258029765788", "705135039569772524273274786652", "170567418260893393020344098265", "401043354947659563658581268242", "746709065616595245635350557925", "739570024549618413776557843034", "184597012262496958610853505745", "689811400727818703807051112784", "894453010121164288965541305235", "323145029073008946088869964941", "834269564400729646453274750586", "538976762970745472202055589093", "765511399939087047106252621388", "906733295711605356366138410423", "107653940551700559321642810836", "428402693021051075533830345295", "386782660475155103347385287948", "936626025836194580089064628716", "718522629491464055045890912121", "370656945845300237607868352243", "951908186614186444840337711498", "535178875249889835014025850038", "505970047705717604298603983975", "484398304612602344941130624527", "048342694079170795987835013947", "860331019262176299872846206272", "549663926438975145562538360932", "329735455392841851511474791078", "711755200061373546828858448100", "778808866574640894148527759780"};
vstring ones = {"050738147930236727719964251439", "804492562859282318664226330103", "610197568193830684654773608216", "279000416545607314567843085541", "782201171759873927350740022455", "043370803444176631019883186675", "566092086050401228622782761449", "469598907881602996036692882305", "116923500417992303845370254124", "796876115092839169954790509461", "783836410405270687557924090071", "095144151150833738671751747749", "354474585664039135189964700948", "328968176148004939648962631420", "829651915384290848347221555092", "170980383407813034573738951375", "728655435703349509419725538350", "121896684176286430427852435647", "315710894574884960021671476788", "592177839598531202003634382961", "876587919610157913350259498196", "505517243779897451333006271744", "618607877753891664471800511372", "826358757330233811836040764274", "206641252044293046424432092833", "704519364781672964993499009545", "624793571592392775564426440338", "571938479010503551295729304078", "077967252884369103891335711508", "870185204806328841827105139840"};




    GreedyTravellingSalesman A;

    A.worstDistance(thousands,hundreds,tens,ones);




}
