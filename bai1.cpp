#include <iostream>
#include <cctype>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<string> variableGenerator(string tempstr)
{
   vector<string> conditionList;
   vector<string> variableList;
   size_t position = 0;
   string target;

   tempstr.erase(remove_if(tempstr.begin(), tempstr.end(), ::isspace),tempstr.end());

   while((position = tempstr.find("AND")) != tempstr.npos)
   {
       target = tempstr.substr(0, position);
       conditionList.push_back(target);
       tempstr.erase(0, position + 3);
   }

   if((position = tempstr.find("THEN")) != tempstr.npos)
   {
       target = tempstr.substr(0, position);
       conditionList.push_back(target);
       tempstr.erase(0, position + 4);

       conditionList.push_back(tempstr);
   }

   for(int i = 0; i < conditionList.size(); i++)
   {
       if((position = conditionList[i].find("=")) != conditionList[i].npos)
       {
           target = conditionList[i].substr(0, position);
           variableList.push_back(target);
           conditionList[i].erase(0, position + 1);

           variableList.push_back(conditionList[i]);
       }
   }

   return variableList;
}

string inferenceEngineBack(map<string, int> conlusionList, map<int, string> knowledgeBase)
{
    bool checkInput = false;
    char pChoice;
    string conclusion,
           tempstr,
           iChoice;
    vector<string> variables;

    /*** prompt interface 1 ***/
    //prompt the conclusion first
    while(!checkInput)
    {
        cout << "Please tell us which Profession you are interested in below:" << endl;
        cout << "A. Engineering   (EGR)" << endl;
        cout << "B. Science       (SCI)" << endl;
        cout << "C. Medical       (MED)" << endl;
        cout << "D. Health Care   (HTC)" << endl;
        cout << "E. Business      (BUS)"<< endl;
        cout << "F. Communication (COM)" << endl;
        cout << "G. Liberal Arts  (LBA)" << endl;
        cout << "H. Applied Arts  (APA)" << endl;
        cout << "I. Fine Arts     (FNA)" << endl;
        cout << "J. Education     (EDU)" << endl;
        cin >> pChoice;

        if(pChoice == 'a' || pChoice == 'A')
        {
            conclusion = "EGR";
            checkInput = true;
        }
        else if(pChoice == 'b' || pChoice == 'B')
        {
            conclusion = "SCI";
            checkInput = true;
        }
        else if(pChoice == 'c' || pChoice == 'C')
        {
            conclusion = "MED";
            checkInput = true;
        }
        else if(pChoice == 'd' || pChoice == 'D')
        {
            conclusion = "HTC";
            checkInput = true;
        }
        else if(pChoice == 'e' || pChoice == 'E')
        {
            conclusion = "BUS";
            checkInput = true;
        }
        else if(pChoice == 'f' || pChoice == 'F')
        {
            conclusion = "COM";
            checkInput = true;
        }
        else if(pChoice == 'g' || pChoice == 'G')
        {
            conclusion = "LBA";
            checkInput = true;
        }
        else if(pChoice == 'h' || pChoice == 'H')
        {
            conclusion = "APA";
            checkInput = true;
        }
        else if(pChoice == 'i' || pChoice == 'I')
        {
            conclusion = "FNA";
            checkInput = true;
        }
        else if(pChoice == 'j' || pChoice == 'J')
        {
            conclusion = "EDU";
            checkInput = true;
        }
        else
            cout << "ERROR! Invalid input, Please choose again!" << endl;
    }

    tempstr = knowledgeBase[conlusionList[conclusion]];

    variables = variableGenerator(tempstr);

    for(int i = 0; i < (variables.size() - 2) ; i += 2)
    {
        cout << "Are you interested in " << variables[i] << "? (yes/no)" << endl;
        cin >> iChoice;

        if(iChoice != variables[i + 1])
        {
            cout << endl;
            cout << conclusion << " is NOT the right Profession for you! Please choose another Profession!" << endl;
            cout << "==========================================================================" << endl;
            cout << "                    END of Backward Chaiing Process!" << endl;
            cout << endl;
            return "UND";
        }
    }

    cout << endl;
    cout << "Good News! " << conclusion << " is the Profession for you!" << endl;
    cout << "=========================================" << endl;
    cout << "    END of Backward Chaiing Process!" << endl;
    cout << endl;

    return conclusion;
}

string Profession_BW()
{
   vector<string> variableList;
   map <string, int> conclusionList;
   map <int, string> knowledgeBase;

   /*** conclusion list ***/

   conclusionList["EGR"] = 10;      //conclusion profession = Engineering   match Rule 10
   conclusionList["SCI"] = 20;      //conclusion profession = Science       match Rule 20
   conclusionList["MED"] = 30;      //conclusion profession = Medical       match Rule 30
   conclusionList["HTC"] = 40;      //conclusion profession = Health Care   match Rule 40
   conclusionList["BUS"] = 50;      //conclusion profession = Business      match Rule 50
   conclusionList["COM"] = 60;      //conclusion profession = Communication match Rule 60
   conclusionList["LBA"] = 70;      //conclusion profession = Liberal Arts  match Rule 70
   conclusionList["APA"] = 80;      //conclusion profession = Applied Arts  match Rule 80
   conclusionList["FNA"] = 90;      //conclusion profession = Fine Arts     match Rule 90
   conclusionList["EDU"] = 100;     //conclusion profession = Education     match Rule 100

   /*** knowledge base ***/

   /** Rule 01 **/
   knowledgeBase[10] = "science = yes AND designing = yes THEN profession = EGR";
   /** Rule 02 **/
   knowledgeBase[20] = "science = yes AND experiment = yes THEN profession = SCI";
   /** Rule 03 **/
   knowledgeBase[30] = "science = yes AND experiment = no THEN profession = MED";
   /** Rule 04 **/
   knowledgeBase[40] = "science = yes AND nursing = yes THEN profession = HTC";
   /** Rule 05 **/
   knowledgeBase[50] = "science = no AND art = yes AND communicate = yes AND decisionMaking = yes THEN profession = BUS";
   /** Rule 06 **/
   knowledgeBase[60] = "science = no AND art = yes AND communicate = yes AND decisionMaking = no THEN profession = COM";
   /** Rule 07 **/
   knowledgeBase[70] = "science = no AND art = yes AND reading = yes AND writing = yes THEN profession = LBA";
   /** Rule 08 **/
   knowledgeBase[80] = "science = no AND art = yes AND reading = yes AND writing = no THEN profession = APA";
   /** Rule 09 **/
   knowledgeBase[90] = "science = no AND art = yes AND reading = no AND crafting = yes THEN profession = FNA";
   /** Rule 10 **/
   knowledgeBase[100] = "science = no AND art = yes AND grading = yes THEN profession = EDU";

   return inferenceEngineBack(conclusionList, knowledgeBase);
}

void Area_FW(string profession)
{
    string tempstr,
           target,
           answer;
    size_t position = 0;

    vector<string> conditionList;

    map <string, string> knowledgeBase;

    knowledgeBase["EGR"] = "electronics, Electrical, machine, Mechanical, construction, Civil, oil, Petroleum, chemistry, Chemical";
    knowledgeBase["SCI"] = "livingBeings, Biology, physicalRules, Physics, compters, CompterScience, chemicalReactions, Chemistry, livestock, AnimalScience";
    knowledgeBase["MED"] = "humanMind, MentalHealth, cancerTreatment, Oncologist, heart, Cardiologist, musculoskeletalSystem, Orthopedic, generalCare, GeneralPractitioner";
    knowledgeBase["HTC"] = "caring, Nursing, management, HealthServiceManagement, admistration, HeathCareAdministration, perscription, PhyscianAssistant, publicProtection, PublicHealth";
    knowledgeBase["BUS"] = "decisionMaking, BusinessManagement, planning, Marketing, promoting, Advertisement, bargaining, Trading, investment, Entrepreneurship,";
    knowledgeBase["COM"] = "investigation, Journalism, language, Linguistics, politics, PoliticalScience, presentation, Speech, styling, Editing";
    knowledgeBase["LBA"] = "statistics, Anthropology, space, Astronomy, worldCulture, WorldLiterature, reading, Literature, religon, Theology";
    knowledgeBase["APA"] = "pictures, Photography, creating, Design, painting, VisualCommunication, graphics, Media, trending, Fashion";
    knowledgeBase["FNA"] = "history, ArtHistory, sculpture, Sculpting, drawing, Painting, melody, Music, performance, Dance";
    knowledgeBase["EDU"] = "elementarySchool, EarlyChildHood, gymnasium, PhysicalEducation, CollegeStudent, SecondaryEducation, disabilityStudent, SpecialEducation, serviceProviding, Conseling";

    tempstr = knowledgeBase[profession];
    tempstr.erase(remove_if(tempstr.begin(), tempstr.end(), ::isspace),tempstr.end());

    while((position = tempstr.find(",")) != tempstr.npos)
    {
       target = tempstr.substr(0, position);
       conditionList.push_back(target);
       tempstr.erase(0, position + 1);
    }

    conditionList.push_back(tempstr);

    for(int i = 0; i < conditionList.size(); i++)
    {
        cout << "Are you interested in " << conditionList[i] << "?" << endl;
        cin >> answer;

        if(answer == "yes")
        {
            cout << endl;
            cout << "Good News!" << conditionList[i + 1] << " is the area suits you!" << endl;
            cout << "========================================" << endl;
            cout << "    END of forward Chaining Process!" << endl;
            cout << endl;
            return;
        }

        else if(answer == "no")
            i++;
    }

    cout << endl;
    cout << "In the profession " << profession << ", there is no area for your. You may want to consider another profession!" << endl;
    cout << "=========================================================================================" << endl;
    cout << "                      END of forward Chaining Process!" << endl;
    cout << endl;
}

int main()
{
    string profession;
    char choice;
    bool end1 = false;

    /*** Main Menu Interface ***/

    cout << "***********************************************************************" << endl;
    cout << "               == Welcome to the Career Advising System! ==" << endl;
    cout << endl;
    cout << "Please Answer the following questions to help us determine your career." << endl;
    cout << "Please choose an option:" << endl;

    while(!end1)
    {
       cout << "A. Start Career Advising." << endl;
       cout << "B. Exit the system" << endl;
       cin >> choice;
       cout << endl;

       if(choice == 'A' || choice == 'a')

       {
            profession = Profession_BW();

            if(profession != "UND")
               Area_FW(profession);
       }

       else if(choice == 'B' || choice == 'b')
        end1 = true;

       else
        cout << "ERROR! Invalid input, Please choose again!" << endl;
    }

    return 0;
}
