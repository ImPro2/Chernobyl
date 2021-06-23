#pragma once

#include "Chernobyl/Core/Core.h"
#include "RenderingResource.h"
#include "Shader.h"

// Vertex buffers, Index buffers, etc.

namespace CH {

	struct BufferElement
	{
		String Name;
		ShaderDataType Type;
		Size Offset;
		uint32 Size;
		bool Normalized;

		BufferElement() = default;
		
		BufferElement(const String& name, ShaderDataType type, bool normalized)
			: Name(name), Type(type), Offset(0), Size(0), Normalized(normalized)
		{
		}

		BufferElement(const String& name, ShaderDataType type, CH::Size offset, uint32 size, bool normalized)
			: Name(name), Type(type), Offset(offset), Size(size), Normalized(normalized)
		{
		}

		uint32 GetComponentCount()
		{
			switch (Type)
			{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Bool:		return 1;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
			}

			CH_CORE_WARN("Unknown shader data type!");
			return 0;
		}
	};


	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() = default;

		VertexBufferLayout(std::initializer_list<BufferElement> list)
			: m_Elements(list) 
		{
			CalculateOffsetsAndStride();
		}

	public:
		void Set(std::initializer_list<BufferElement> list)
		{
			m_Elements = list;
			CalculateOffsetsAndStride();
		}

	public:
		const Vector<BufferElement>& GetElements() const { return m_Elements; }
		uint32                       GetStride()   const { return m_Stride;   }

		int32 GetElementCount() const { return m_Elements.size(); }

		Vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		Vector<BufferElement>::iterator end()   { return m_Elements.end();   }
		Vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		Vector<BufferElement>::const_iterator end()   const { return m_Elements.end();   }

	private:
		void CalculateOffsetsAndStride()
		{
			Size offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				if (element.Size == 0)
					element.Size = ShaderDataTypeToSize(element.Type);

				element.Offset = offset;
				offset        += element.Size;
				m_Stride      += element.Size;
			}
		}

	private:
		Vector<BufferElement> m_Elements;
		uint32 m_Stride = 0;
	};

	class VertexBuffer : public RenderingResource
	{
	public:
		static Ref<VertexBuffer> Create(void* vertices, int32 vertexCount, int32 size, int32 vertexSize);

		VertexBuffer(int32 vertexCount, int32 size, int32 vertexSize);

	public:
		void SetLayout(VertexBufferLayout layout)   { m_Layout = layout; }
		const VertexBufferLayout& GetLayout() const { return m_Layout;   }

	public:
		int32 GetVertexCount() const { return m_VertexCount; }
		int32 GetSize()        const { return m_Size;        }
		int32 GetVertexSize()  const { return m_VertexSize;  }

	protected:
		VertexBufferLayout m_Layout;

		int32 m_VertexCount;
		int32 m_Size;
		int32 m_VertexSize;
	};

	class IndexBuffer : public RenderingResource
	{
	public:
		static Ref<IndexBuffer> Create(u16* indices, int32 count, int32 size);

		IndexBuffer(int32 count, int32 size);

	public:
		int32 GetCount()  const { return m_Count; }
		int32 GetSize()   const { return m_Size;  }

	protected:
		int32 m_Count;
		int32 m_Size;
	};

}