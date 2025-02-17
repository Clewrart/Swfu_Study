using System.Numerics;

namespace RayTracing05
{
    /**
     * 光线类
     */
    public class Ray
    {
        // 光线的原点
        public Vector3 Origin
        {
            get;
        }

        // 光线的方向
        public Vector3 Direction
        {
            get;
        }

        // 构造方法
        public Ray(Vector3 origin, Vector3 direction)
        {
            Origin = origin;
            Direction = direction;
        }

        /**
         * 计算三维空间中光线上任意一点P的三维坐标(x,y,z)
         * 计算公式：P(t) = Origin + t * Direction
         * 其中Origin是光线的起点，Direction是光线的方向，t是参数值。
         */
        public Vector3 PointAtParameter(float t)
        {
            return Origin + t * Direction;
        }
    }
}
