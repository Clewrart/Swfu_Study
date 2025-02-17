using System.Numerics;

namespace RayTracing07
{
    /**
     * 漫反射材质类
     */
    public class Lambertian : Material
    {
        // 反射率
        private readonly Vector3 albedo;

        public Lambertian(Vector3 albedo)
        {
            this.albedo = albedo;
        }

        public override bool Scatter(Ray ray,
                                     HitRecord rec,
                                     out Vector3 attenuation,
                                     out Ray scattered)
        {

            //Vector3 target = rec.P +rec.N + Utility.RandomInUnitSphere(); 
            //scattered = new Ray(rec.P, target - rec.P);
            scattered =new Ray(rec.P,rec.N + Utility.RandomInUnitSphere());
            attenuation = albedo;

            return true;
        }
    }
}
