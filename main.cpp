#include <iostream>
#include <hdf5/serial/H5Cpp.h>
#include <vector>

void processHDF5Group(const H5::Group &group)
{
    try
    {
        // Iterate over all objects in the group
        for (hsize_t i = 0; i < group.getNumObjs(); ++i)
        {
            std::string datasetName = group.getObjnameByIdx(i);
            std::cout << "LMA : datasetName " << datasetName << std::endl;

            // Check if the object is a dataset or subgroup
            if (group.getObjTypeByIdx(i) == H5G_GROUP)
            {
                std::cout << "Entering group: " << datasetName << std::endl;
                H5::Group subgroup = group.openGroup(datasetName);

                // Recursively process the subgroup
                processHDF5Group(subgroup);
            }
            else if (group.getObjTypeByIdx(i) == H5G_DATASET)
            {
                H5::DataSet dataset = group.openDataSet(datasetName);

                // Get the dataspace of the dataset
                H5::DataSpace dataspace = dataset.getSpace();

                // Get the number of elements in the dataset
                hsize_t numElements = dataspace.getSimpleExtentNpoints();

                // Create a vector to hold the data
                std::vector<int> data(numElements);

                // Read the data into the vector
                dataset.read(data.data(), H5::PredType::NATIVE_INT);

                std::cout << "Data from dataset '" << datasetName << "':" << std::endl;
                for (const auto &value : data)
                {
                    std::cout << value << " ";
                }
                std::cout << std::endl;

                std::cout << "Data from dataset '" << datasetName << "':" << std::endl;
                for (const auto &value : data)
                {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
        }
    }
    catch (const H5::Exception &e)
    {
        std::cerr << "Error processing HDF5 group: " << e.getDetailMsg() << std::endl;
    }
}

void readHDF5RawFile(const std::string &fileName)
{
    try
    {
        H5::H5File file(fileName, H5F_ACC_RDONLY);

        // Get the root group
        H5::Group rootGroup = file.openGroup("/");

        // Process the root group
        processHDF5Group(rootGroup);
    }
    catch (const H5::Exception &e)
    {
        std::cerr << "Error reading HDF5 file: " << e.getDetailMsg() << std::endl;
    }
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    readHDF5RawFile("/mnt/c/Users/leila/source/repos/openPMD-example-datasets/example-2d/hdf5/data00000255.h5");
    return 0;
}
