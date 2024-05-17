#include <core/io.hpp>

namespace sable
{

namespace core
{


void write_runtime_to_output(
    const std::string& name,
    const stats::SingleVarStats& runtime_data
)
{
    std::fstream file;
    
    file.open("./sable/" + name + ".csv");

    if (!file.good())
    {
        throw std::fstream::failure("Could not open file to save sable runtime data. ");
    }

    // check if empty file, then add csv headers
    if (file.peek() == std::fstream::traits_type::eof())
    {
        file << "average (ns), stdev (ns), n" << std::endl;
    }

    file << runtime_data.mu << ", " << runtime_data.sigma << ", " << runtime_data.n << std::endl;

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
    file.seekg(EOF);

    char* buf;

    while(true)
	{
		file.unget(); //go back two chars
		file.unget();
		char in = file.get();
		if(in == '\n')
		{
			file.getline(buf, ', ');
            avg = std::stod(buf);

            file.getline(buf, ', ');
            stdev = std::stod(buf);

            file.getline(buf, ', ');
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
