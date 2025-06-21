template <typename EnumType, typename LoaderFunc, typename ConverterFunc>
void SoundConfig::load_category(const YAML::Node& config, const std::string& category,
                               LoaderFunc func_load, ConverterFunc func_convertidor)
{
    if (!config[category]) return;

    for (const auto& node : config[category]) {
        std::string key = node.first.as<std::string>();
        std::string path = node.second.as<std::string>();

        try {
            EnumType id = func_convertidor(key);
            func_load(id, path);
        } catch (const std::exception& e) {
            std::cerr << "Error cargando " << category << ": " << e.what() << std::endl;
        }
    }
}
