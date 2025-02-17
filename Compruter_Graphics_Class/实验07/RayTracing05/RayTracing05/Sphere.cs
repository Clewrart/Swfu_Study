using System.Numerics;

namespace RayTracing05
{
    /**
     * 球体类，实现IHitable接口。
     */
    public class Sphere : IHitable
    {
        // 球体中心
        public Vector3 Center { get; }

        // 球体半径
        public float Radius { get; }

        /**
         * 构造方法
         */
        public Sphere(Vector3 center, float radius)
        {
            Center = center;
            Radius = radius;
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
            float discriminant = b * b - 4.0f * a * c;

            if (discriminant < 0)
            {
                return false;
            }

            float root = (-b - MathF.Sqrt(discriminant)) / (2.0f * a);
            if (root < tMin || root > tMax)
            {
                root = (-b + MathF.Sqrt(discriminant)) / (2.0f * a);
                if (root < tMin || root > tMax)
                {
                    return false;
                }
            }

                rec.T = root;
                rec.P = ray.PointAtParameter(rec.T);
                rec.N = (rec.P - Center) / Radius;
                return true;
            }
        }
    }