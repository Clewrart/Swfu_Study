using System.Numerics;

namespace RayTracing07
{
    public class Utility
    {
        /**
         * 生成单位球面内任意点的坐标
         */
        public static Vector3 RandomInUnitSphere()
        {
            Random rnd = new Random();
            Vector3 p;

            do
            {
                p = 2.0f * new Vector3(
                    rnd.NextSingle(),
                    rnd.NextSingle(),
                    rnd.NextSingle()) -
                    Vector3.One;
            } while (p.LengthSquared() >= 1.0f);

            return p;
        }

        public static Vector3 RandomUnitVector()
        {
            return Vector3.Normalize(RandomInUnitSphere());
        }
    }
}
