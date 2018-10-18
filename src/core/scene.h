#ifndef JPC_CORE_SCENE_H
#define JPC_CORE_SCENE_H
#include <vector>
#include <memory>


/*
Sachen auf die es sich bezieht.
Lights
Primitive
LightFlags::Infinite

*/


namespace rt{

	class Scene {
	//in der Scenen klasse werden alle Objekte und damit alle informationen �ber eine Szene gespeichert
	public:
		//Konstruktor 
		Scene(std::shared_ptr<Primitive> aggregate, const std::vector<std::shared_ptr<Ligth>> &lights)
		:lights(lights), aggregate(aggregate) {
			worldBound = aggregate->WorldBound();
			for (const auto &light : lights) {
				light->Preprocess(*this);
				if (light->flags & (int)LightFlags::Infinite) {
					infiniteLights.push_back(light);
				}
			}
		}

		//Weltbegraenzung
		const Bounds3f &WorldBound() const { return worldBound };
		//gibt zur�ck trifft Strahl auf irgendwelche Primitives
		//Au�erdem fuellt es Daten in die SurfaceInteraction �ber den n�chsten Punkt, an dem der Strahl diese trifft.
		bool Intersect(const Ray &ray, SurfaceInteraction *isect) const;
		//gibt nur zur�ck ob ei Strahl auf irgendwelche Primitives trifft.
		//Bessere Performance aus Intersect
		bool IntersectP(const Ray &ray) const;

		//Die Funktionsweise noch nicht nach geschaut
		bool IntersectTr(Ray ray, Sampler &sampler, SurfaceInteraction *isert, Spectrum *transmittance) const;

	
		//alle Lichter der Szene. Auch die unendlich entfernten Lichter
		std::vector<std::shared_ptr<Light>> lights;

		//unendlich entfernte Lichter in einem Seperaten Vector, um diese seperate durch zu loopen
		std::vector<std::shared_ptr<Light>> infiniteLights;

	private:
		std::shared_ptr<Primitive> aggregate;
		Bounds3f worldBound;



};


}

#endif