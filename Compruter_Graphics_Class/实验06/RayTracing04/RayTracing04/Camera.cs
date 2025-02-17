using System.Numerics;

namespace RayTracing04
{
    /**
     * 虚拟相机类
     */
    public class Camera
    {
        // 相机坐标系原点
        private Vector3 origin;

        // 投影平面左下角顶点的三维坐标
        private Vector3 lowerLeftCorner;

        // 投影平面在三维世界坐标系中的宽度。
        private Vector3 horizontal;

        // 投影平面在三维世界坐标系中的高度
        private Vector3 vertical;

        /**
         * 构造方法
         */
        public Camera()
        {
            origin = Vector3.Zero;
            lowerLeftCorner = new Vector3(-2.0f, -1.0f, -1.0f);
            horizontal = new Vector3(4.0f, 0.0f, 0.0f);
            vertical = new Vector3(0.0f, 2.0f, 0.0f);
        }

        /**
         * 从相机原点到投影平面(u,v)处发射一条光线
         */
        public Ray GetRay(float u, float v)
        {
            return new Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
        }
    }
}
