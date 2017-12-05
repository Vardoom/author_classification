#include <QCoreApplication>
#include <iostream>
#include <Preprocessing/text.h>

/*
std::vector<Features> createFeaturesForDatabase(int iterations){
    std::ifstream fichier("../data/final_index.json"); // mettre le json dans le projet ///////////////
    std::vector<Features> vectorFeatures;
    if(fichier){ // checking if file opening worked
        std::string ligne;
        getline(fichier, ligne);
        fichier.close();

        // Delete the beggining and the end of the string
        ligne.erase(0, 2);
        ligne.erase(ligne.length() - 2, 2);

        // Determine the delimiter
        std::string delimiter = "}, {";
        size_t pos = 0;
        std::string token;
        int compteur;
        compteur = 0;
        while ((pos = ligne.find(delimiter)) != std::string::npos && compteur < iterations) {
            std::cout << "New text read in the database" << std::endl;
            token = ligne.substr(0, pos);

            size_t posInt = 0;
            text textIntern;
            std::string deliInter;

            // Get Title
            token.erase(0, 10);
            deliInter = "\", \"id\": \"";
            posInt = token.find(deliInter);
            textIntern.title = token.substr(0, posInt);
            std::cout << "Title acquired" << std::endl;

            // Get id
            token.erase(0, posInt + 10);
            deliInter = "\", \"number_of_lines\": ";
            posInt = token.find(deliInter);
            char * pEnd;
            textIntern.id = std::strtol((token.substr(0, posInt)).c_str(), &pEnd, 10);
            std::cout << "Id acquired" << std::endl;

            // Get number_of_lines
            token.erase(0, posInt + 21);
            deliInter = ", \"author\": \"";
            posInt = token.find(deliInter);
            textIntern.number_of_lines = std::strtol((token.substr(0, posInt)).c_str(), &pEnd, 10);
            std::cout << "Number of lines acquired" << std::endl;

            // Get author
            token.erase(0, posInt + 13);
            deliInter = "\"";
            posInt = token.find(deliInter);
            textIntern.author = token.substr(0, posInt);
            std::cout << "Author acquired" << std::endl;

            ligne.erase(0, pos + delimiter.length());

            // Create blockList
            textIntern.createBlockList();
            std::cout << "BlockList acquired" << std::endl;

            // Create blocks from blockList (functions)
            for(int i=0; i< textIntern.blockList.size(); i++){
                textIntern.blockList[i].updateCharFrequency();
                textIntern.blockList[i].updateDifferentWordsCount();
                textIntern.blockList[i].updateSentenceCount();
                textIntern.blockList[i].updateUnicWordsCount();
                textIntern.blockList[i].updateWordCount();
                textIntern.blockList[i].updateWordFrequency();
                textIntern.blockList[i].updateSubordinationsCount();
            }
            std::cout << "Block's functions for BlockList processed" << std::endl;

            // Create features
            vector<Features> featuresIntern;
            featuresIntern = textIntern.agregate();
//            std::cout << text::floatToString(featuresIntern.charFrequency.size())<< std::endl;
//            std::cout << text::floatToString(featuresIntern.sentenceCount) << std::endl;
//            std::cout << text::floatToString(featuresIntern.wordCount) << std::endl;
//            std::cout << text::floatToString(featuresIntern.wordFrequency.size()) << std::endl;
            std::cout << "Features generated" << std::endl;

            for (int i=0;i< featuresIntern.size();i++){vectorFeatures.push_back(featuresIntern.at(i));}
            compteur += 1;
        }
    }else{
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }
    return(vectorFeatures);
}
*/

std::map<int, std::string> createTextFeatures(int iterations){
    std::ifstream fichier("../data/final_index.json");
    int compteurMap = 0;
    std::map<int, std::string> idToAuthor;
    std::map<std::string, int> authorToId;

    if(fichier){ // checking if file opening worked
        std::string ligne;
        getline(fichier, ligne);
        fichier.close();

        // Delete the beggining and the end of the string
        ligne.erase(0, 2);
        ligne.erase(ligne.length() - 2, 2);

        // Determine the delimiter
        std::string delimiter = "}, {";
        size_t pos = 0;
        std::string token;
        int compteur;
        compteur = 0;
        while ((pos = ligne.find(delimiter)) != std::string::npos && compteur < iterations) {
            std::cout << "=============================" << std::endl;
            std::cout << "New text read in the database" << std::endl;
            std::cout << "Iteration: " << compteur << std::endl;
            token = ligne.substr(0, pos);

            size_t posInt = 0;
            text textIntern;
            std::string deliInter;

            // Get Title
            token.erase(0, 10);
            deliInter = "\", \"id\": \"";
            posInt = token.find(deliInter);
            textIntern.title = token.substr(0, posInt);
            std::cout << "Title acquired" << std::endl;

            // Get id of the text
            token.erase(0, posInt + 10);
            deliInter = "\", \"number_of_lines\": ";
            posInt = token.find(deliInter);
            char * pEnd;
            textIntern.id = std::strtol((token.substr(0, posInt)).c_str(), &pEnd, 10);
            std::cout << "Id of the text acquired" << std::endl;

            // Get number_of_lines
            token.erase(0, posInt + 21);
            deliInter = ", \"author\": \"";
            posInt = token.find(deliInter);
            textIntern.number_of_lines = std::strtol((token.substr(0, posInt)).c_str(), &pEnd, 10);
            std::cout << "Number of lines acquired" << std::endl;

            // Get author
            token.erase(0, posInt + 13);
            deliInter = "\"";
            posInt = token.find(deliInter);
            textIntern.author = token.substr(0, posInt);
            if (authorToId.count(textIntern.author) == 0){
                idToAuthor.insert(std::pair<int, string>(compteurMap, textIntern.author));
                authorToId.insert(std::pair<string, int>(textIntern.author, compteurMap));
                compteurMap += 1;
            }
            textIntern.idAuthor = authorToId[textIntern.author];
            std::cout << "Id Author: " << authorToId[textIntern.author] << " Author Name: " << textIntern.author << std::endl;
            std::cout << "Author acquired" << std::endl;

            ligne.erase(0, pos + delimiter.length());

            // Create blockList
            textIntern.createBlockList();
            std::cout << "BlockList acquired" << std::endl;

            // Create blocks from blockList (functions)
            for(int i=0; i< textIntern.blockList.size(); i++){
                textIntern.blockList[i].updateCharFrequency();
                textIntern.blockList[i].updateDifferentWordsCount();
                textIntern.blockList[i].updateSentenceCount();
                textIntern.blockList[i].updateUnicWordsCount();
                textIntern.blockList[i].updateWordCount();
                textIntern.blockList[i].updateWordFrequency();
                textIntern.blockList[i].updateSubordinationsCount();
            }
            std::cout << "Block's functions for BlockList processed" << std::endl;

            // Create features
            vector<Features> featuresIntern;
            featuresIntern = textIntern.agregate();
//            std::cout << text::floatToString(featuresIntern.charFrequency.size())<< std::endl;
//            std::cout << text::floatToString(featuresIntern.sentenceCount) << std::endl;
//            std::cout << text::floatToString(featuresIntern.wordCount) << std::endl;
//            std::cout << text::floatToString(featuresIntern.wordFrequency.size()) << std::endl;
            std::cout << "Features generated" << std::endl;
            for (int i=0;i<featuresIntern.size();i++){featuresIntern.at(i).createcsv();}

            compteur += 1;
        }
    }else{
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }
    return idToAuthor;
}

int main(int argc, char *argv[])
{
    int nbriteration = 10;
    std::map<int, std::string> idToAuthor;
    idToAuthor = createTextFeatures(nbriteration);
    return 0;
}
