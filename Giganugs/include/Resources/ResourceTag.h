#pragma once
namespace Giganugs::Resources {
	template <class T>
	class ResourceTag
	{
	private:
		uint32_t ID;
	public:
		ResourceTag() : ID(0) {}
		ResourceTag(uint32_t ID) : ID(ID) {}
		ResourceTag(const ResourceTag<T>& other) : ID(other.ID) {}

		uint32_t id() const { return ID; }
	};

	template<class T>
	bool operator ==(const ResourceTag<T>& a, const ResourceTag<T>& b) {
		return a.id() == b.id();
	}
}

namespace std {
	template <class T> struct hash<Giganugs::Resources::ResourceTag<T>>
	{
		size_t operator()(const Giganugs::Resources::ResourceTag<T> & x) const
		{
			return hash<uint32_t>()(x.id());
		}
	};
}
