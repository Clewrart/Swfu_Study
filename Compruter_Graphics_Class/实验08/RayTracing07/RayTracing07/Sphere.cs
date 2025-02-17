using System.Numerics;

namespace RayTracing07
{
    /**
     * 球体类
     */
    public class Sphere : IHitable
    {
        // 球体中心
        public Vector3 Center
        {
            get;
        }

        // 球体半径
        public float Radius
        {
            get;
        }

        // 球体材质
        public Material Mat
        {
            get;
        }

        /**
         * 构造方法
         */
        public Sphere(Vector3 center, float radius, Material material)
        {
            Center = center;
            Radius = radius;
            Mat = material;
        }

        /**
         * 判断某条光线是否与球体相交
         */
        public bool Hit(Ray ray, float tMin, float tMax, HitRecord rec)
        {
            Vector3 oc = ray.Origin - Center;
            float a = Vector3.Dot(ray.Direction, ray.Direction);
            float b = 2.0f * Vector3.Dot(oc, ray.Direction);
            float c = Vector3.Dot(oc, oc) - Radius * Radius;
            float discriminant = b * b - 4.0f * a * c;//b2-4ac

            if (discriminant < 0)
            {
                return false;
            }

            float root = (-b - MathF.Sqrt(discriminant)) / (2.0f * a); //减法形计算二次方程的一个根

            //检查root?在区间 [tMin, tMax] 内
            if (root < tMin || root > tMax)
            {
                //第一个根不在区间用加法形
                root = (-b + MathF.Sqrt(discriminant)) / (2.0f * a);

                //再次检查第二个根是否落在区间 [tMin, tMax] 内
                if (root < tMin || root > tMax)
                {
                    //如果第二个根也不在范围内，则表明射线与物体在此区间内无交点
                    return false; 
                }
            }

            rec.T = root;
            rec.P = ray.PointAtParameter(rec.T);
            rec.N = (rec.P - Center) / Radius;
            rec.M = Mat;

            return true;
        }
    }
}
