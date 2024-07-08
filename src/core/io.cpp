#include <core/io.hpp>

namespace sable
{

namespace core
{

namespace
{

inline bool is_file_empty(std::fstream& file)
{
    file.seekp(0, std::ios::end);
    return file.tellg() == 0;
}

}

void write_runtime_to_output(
    const std::string& name,
    const stats::SingleVarStats& runtime_data
)
{
    std::fstream file;

    if (!std::filesystem::exists("./sable/"))
    {
        std::filesystem::create_directory("./sable");
    }
    
    file.open("./sable/" + name + ".csv", std::fstream::out | std::fstream::in | std::fstream::app);

    if (!file.good())
    {
        throw std::fstream::failure("Could not open file to save sable runtime data. ");
    }

    // check if empty file, then add csv headers
    if (is_file_empty(file))
    {
        file << "average (ns), stdev (ns), n" << std::endl;
    }

    file << runtime_data.mean << "," << runtime_data.variance << "," << runtime_data.n << std::endl;

    file.close();
}

std::optional<const stats::SingleVarStats> get_last_runtime(
    const std::string& name
)
{
    std::ifstream file;

    file.open("./sable/" + name + ".csv");

    // check if file is empty, if so, return nullopt
    if (!file.good())
    {
        return {};
    }

    // go to last line in file

    
    size_t n;
    double avg, stdev;

    // read in reverse order
    file.seekg(0, std::ios::end);

    char buf[8];

    while(true)
	{
		file.unget(); //go back two chars
        file.unget();
		char in = file.get();

		if(in == '\n')
		{
			file.getline(buf, 8, ',');
            avg = std::stod(buf);

            file.getline(buf, 8, ',');
            stdev = std::stod(buf);

            file.getline(buf, 8, '\n');
            n = std::stoull(buf);

			break;
		}
	}

    return stats::SingleVarStats{
        n, avg, stdev
    };

}

} // namespace core

} // namespace sable
