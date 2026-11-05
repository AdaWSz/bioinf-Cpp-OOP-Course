#include <string>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
namespace fs = std::filesystem;

class Sequence { //assuming nucleotide sequence.
	private:
	    std::unordered_set<char> legalNucleo{'A', 'T', 'G', 'C', 'U', 'N'};
		struct Metadata {
		    std::string name;
			std::string source; //Database or experiment
		};
		std::string seq;
		std::unordered_map<char,long> nucleoCount;
		Metadata metadata;
		long seqLength;

	public:
	    Sequence() {

				seq = "";
				metadata.name = "";
				metadata.source = "";
				nucleoCount = {{'A', 0},{'T', 0},{'G', 0},{'C', 0},{'U', 0},{'N', 0}};

				}

		const std::string& GetSequence() { //by reference
			return seq;
		};

		const std::string& GetSource() {
		    return metadata.source;
		}

		const std::string& GetName() {
		    return metadata.name;
		}

		const std::unordered_map<char, long>& GetNucleotideCounts() {
		    return nucleoCount;
		}

		void ParseSequence() {
		    for(char& c: seq) {
				c = toupper(static_cast<unsigned char>(c));
				if(legalNucleo.find(c) == legalNucleo.end()) {
				    c = 'N';
				}
			}
		}

		void LoadFASTA(const std::string& file_path) {
		    if (!fs::exists(file_path))
				return;

			const fs::path filepath(file_path);
			std::ifstream fasta(filepath.string());
			std::string line;
			if(!fasta.is_open()) {
			    std::cerr<< "Could not open file: " << filepath.string() << std::endl;
				return;
			}
			while (std::getline(fasta, line)) {
                if (!line.empty() and line[0] == '>') {
                    metadata.name = line.substr(1);
                }
                else if (!line.empty()) {
                    seq += line;
                }
            }
		}

		void CountNucleotides() {
            for(const char& c: seq) {
                if(nucleoCount.find(c) != nucleoCount.end()) {
                    ++nucleoCount.at(c);
                }
            }
		}
};

int main() {

    Sequence test_seq;
    std::string file_path = "./example.fasta";

    test_seq.LoadFASTA(file_path);
    std::string loaded_name = test_seq.GetName();
    std::string loaded_seq = test_seq.GetSequence();
    std::cout << "Loaded sequence name: " << loaded_name << std::endl;
    std::cout << "Loaded sequence: " << loaded_seq << std::endl;
    test_seq.CountNucleotides();
    std::unordered_map <char, long> nucleo_counts = test_seq.GetNucleotideCounts();
    std::cout << "Nucleotide counts:" << std::endl;
    for (auto i : nucleo_counts)
        if (i.second != 0)
            std::cout << i.first << ": " << i.second << std::endl;
    return 0;
}
