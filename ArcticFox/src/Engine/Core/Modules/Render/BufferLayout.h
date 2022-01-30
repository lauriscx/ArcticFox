#pragma once
#include <string>
#include <vector>

namespace ArcticFox {
	namespace Graphics {
		enum class DataType {
			NONE = 0,
			FLOAT_1,
			FLOAT_2,
			FLOAT_3,
			FLOAT_4,
			FLOAT_9,
			FLOAT_16,
			UINT_1,
			UINT_2,
			UINT_3,
			UINT_4,
			UINT_9,
			UINT_16,
			INT_1,
			INT_2,
			INT_3,
			INT_4,
			INT_9,
			INT_16,
			BOOL_1,
			BOOL_2,
			BOOL_3,
			BOOL_4,
			BOOL_9,
			BOOL_16,
			COUNT
		};

		struct BufferElement {
		private:
			unsigned int DataSize(DataType type) {
				switch (type) {
				case Graphics::DataType::NONE:		return 0;
				case Graphics::DataType::FLOAT_1:	return 4 * 1;
				case Graphics::DataType::FLOAT_2:	return 4 * 2;
				case Graphics::DataType::FLOAT_3:	return 4 * 3;
				case Graphics::DataType::FLOAT_4:	return 4 * 4;
				case Graphics::DataType::FLOAT_9:	return 4 * 9;
				case Graphics::DataType::FLOAT_16:	return 4 * 16;
				case Graphics::DataType::UINT_1:	return 4 * 1;
				case Graphics::DataType::UINT_2:	return 4 * 2;
				case Graphics::DataType::UINT_3:	return 4 * 3;
				case Graphics::DataType::UINT_4:	return 4 * 4;
				case Graphics::DataType::UINT_9:	return 4 * 9;
				case Graphics::DataType::UINT_16:	return 4 * 16;
				case Graphics::DataType::INT_1:		return 4 * 1;
				case Graphics::DataType::INT_2:		return 4 * 2;
				case Graphics::DataType::INT_3:		return 4 * 3;
				case Graphics::DataType::INT_4:		return 4 * 4;
				case Graphics::DataType::INT_9:		return 4 * 9;
				case Graphics::DataType::INT_16:	return 4 * 16;
				case Graphics::DataType::BOOL_1:	return 1 * 1;
				case Graphics::DataType::BOOL_2:	return 1 * 2;
				case Graphics::DataType::BOOL_3:	return 1 * 3;
				case Graphics::DataType::BOOL_4:	return 1 * 4;
				case Graphics::DataType::BOOL_9:	return 1 * 9;
				case Graphics::DataType::BOOL_16:	return 1 * 16;
				case Graphics::DataType::COUNT:		return 0;
				default: return 0;
				}
			}
			unsigned int DataCompoenentCount(DataType type) {
				switch (type) {
				case Graphics::DataType::NONE:		return 0;
				case Graphics::DataType::FLOAT_1:	return 1;
				case Graphics::DataType::FLOAT_2:	return 2;
				case Graphics::DataType::FLOAT_3:	return 3;
				case Graphics::DataType::FLOAT_4:	return 4;
				case Graphics::DataType::FLOAT_9:	return 9;
				case Graphics::DataType::FLOAT_16:	return 16;
				case Graphics::DataType::UINT_1:	return 1;
				case Graphics::DataType::UINT_2:	return 2;
				case Graphics::DataType::UINT_3:	return 3;
				case Graphics::DataType::UINT_4:	return 4;
				case Graphics::DataType::UINT_9:	return 9;
				case Graphics::DataType::UINT_16:	return 16;
				case Graphics::DataType::INT_1:		return 1;
				case Graphics::DataType::INT_2:		return 2;
				case Graphics::DataType::INT_3:		return 3;
				case Graphics::DataType::INT_4:		return 4;
				case Graphics::DataType::INT_9:		return 9;
				case Graphics::DataType::INT_16:	return 16;
				case Graphics::DataType::BOOL_1:	return 1;
				case Graphics::DataType::BOOL_2:	return 2;
				case Graphics::DataType::BOOL_3:	return 3;
				case Graphics::DataType::BOOL_4:	return 4;
				case Graphics::DataType::BOOL_9:	return 9;
				case Graphics::DataType::BOOL_16:	return 16;
				case Graphics::DataType::COUNT:		return 0;
				default: return 0;
				}
			}
		public:
			std::string m_Name;
			DataType m_Type;
			unsigned int m_Size;
			unsigned int m_Offset;
			bool m_Normalized;
			unsigned int m_Components;

			BufferElement() {}
			BufferElement(const std::string& name, DataType type, bool normalized = false) :
				m_Name(name),
				m_Type(type),
				m_Size(DataSize(type)),
				m_Offset(0),
				m_Normalized(normalized),
				m_Components(DataCompoenentCount(type))
			{}
		};

		class BufferLayout {
		public:
			BufferLayout() {}
			BufferLayout(const std::vector<BufferElement>& elements) : m_Elements(elements) { PrepereElements(); }//Creates layout with std::vector
			BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) { PrepereElements(); }//Creates layout with raw array with implicit cast to std::vector
			inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
			inline unsigned int GetStride() const { return m_Stride; }

			std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); };
			std::vector<BufferElement>::iterator end() { return m_Elements.end(); };

		private:
			void PrepereElements() {
				unsigned int offset = 0;
				m_Stride = 0;
				for (auto& element : m_Elements) {
					element.m_Offset = offset;
					offset += element.m_Size;
					m_Stride += element.m_Size;
				}
			}

		private:
			std::vector<BufferElement> m_Elements;
			unsigned int m_Stride;
		};
	}
}