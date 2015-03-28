
template< typename ID, typename Resource >
ResourceManager< ID, Resource >::ResourceManager()
{

}

template< typename ID, typename Resource >
/**
 * Load resource using an enum specific to the
 * type of resource you want to load as a key and
 * a file path to the actual resource you are loading in
 */
void ResourceManager< ID, Resource >::load( ID id, const std::string& file )
{
	std::unique_ptr< Resource > resource( new Resource() );

	if ( !resource -> loadFromFile( file ) )
	{
		std::cout << "\nFailed to load file: " + file << std::endl;
	}

	auto inserted = m_resources.insert( std::make_pair( id, std::move( resource ) ) );

	assert( inserted.second );
}

template< typename ID, typename Resource >
/**
 * Retrieve a specific resource using a Resource
 * enum as an ID
 */
Resource& ResourceManager< ID, Resource >::getResource( ID id )
{
	auto resource = m_resources.find( id );

	return *resource -> second;
}