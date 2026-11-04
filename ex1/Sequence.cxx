#include <string>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;

class Sequence { //assuming nucleotide sequence.
	private:
	    std::unordered_set<char> legal_nucleo{'A', 'T', 'G', 'C', 'U', 'N'};
		struct Metadata {
		    std::string name;
			std::string source; //Database or experiment
		};
		std::string seq;
		Metadata metadata;
		long seqLength;

	public:
	    Sequence() {

				seq = "";
				metadata.name = "";
				metadata.source = "";
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

		void ParseSequence() {
		    for(char& c: seq) {
				c = toupper(static_cast<unsigned char>(c));
				if(legal_nucleo.find(c) == legal_nucleo.end()) {
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
};

int main() {

    Sequence test_seq;
    std::string file_path = "./sequence.fasta";

    test_seq.LoadFASTA(file_path);
    std::string loaded_name = test_seq.GetName();
    std::string loaded_seq = test_seq.GetSequence();
    std::cout << "Loaded sequence name: " << loaded_name << std::endl;
    std::cout << "Loaded sequence: " << loaded_seq << std::endl;
}
