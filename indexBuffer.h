class IndexBuffer {
public:
	IndexBuffer(const unsigned* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const {
		return mCount;
	}
private:
	unsigned int mRendererID;
	unsigned int mCount;
};

