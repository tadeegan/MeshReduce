class Vec3{
    public:
        Vec3(float x, float y, float z);

    private:
        float x;
        float y;
        float z;

        void copy(const Vec3 &source);
        void clear();
};